import numpy as np
from typing import Tuple
from ..types.ennui_types import Vector3, Matrix3x3
from ..geodetic import wgs84 as geode
from ..math.rotation import R3_to_SO3, R3_to_so3, normalize_SO3_Groves


def fwd_pva_S03(
    position_minus: Vector3[np.double],
    velocity_minus: Vector3[np.double],
    attitude_minus: Matrix3x3[np.double],
    gravitation: Vector3[np.double],
    f: Vector3[np.double],
    w: Vector3[np.double],
    dt: np.double,
) -> Tuple[Vector3[np.double], Vector3[np.double], Matrix3x3[np.double]]:
    """Forward progpagation of position, velocity, and attitude \
    using inertial measurements"""
    Omega = R3_to_so3([0, 0, geode.EARTH_ROTATION_RATE])

    # Integrate, constant-rate assumption
    alpha = w * dt
    # Eq. (5.69) [@groves_principles_2013]
    Rb_prop = R3_to_SO3(alpha)

    # Propagate attitude
    #
    # Eq. (5.75) [@groves_principles_2013]
    attitude_plus = attitude_minus @ Rb_prop - dt * Omega @ attitude_minus
    attitude_plus = normalize_SO3_Groves(attitude_plus)

    # Eq. (5.84) [@groves_principles_2013]
    alpha_norm = np.linalg.norm(alpha)
    Rb_smear = np.eye(3)
    if alpha_norm > 1e-10:
        alpha_cross = R3_to_so3(alpha)
        Rb_smear += (1 - np.cos(alpha_norm)) / (
            alpha_norm * alpha_norm
        ) * alpha_cross + (1 - np.sin(alpha_norm) / alpha_norm) / (
            alpha_norm * alpha_norm
        ) * (
            alpha_cross @ alpha_cross
        )

    # Eq. (5.85) [@groves_principles_2013]
    Reb_adj = attitude_minus @ Rb_smear - 0.5 * dt * Omega @ attitude_minus
    fe_ib = Reb_adj @ f

    # Propagate (acceleration) velocity and position
    #
    # Eq. (5.36), using Eq. (2.132) [@groves_principles_2013]
    ae_eb = (
        fe_ib
        + gravitation
        - Omega @ Omega @ position_minus
        - 2 * Omega @ velocity_minus
    )
    velocity_plus = velocity_minus + ae_eb * dt
    # Eq. (5.38) [@groves_principles_2013]
    position_plus = position_minus + 0.5 * dt * (2 * velocity_plus - ae_eb * dt)

    return (position_plus, velocity_plus, attitude_plus)
