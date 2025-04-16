import numpy as np
from ..types.ennui_types import Vector3
from . import wgs84 as geode


def gravitation_ecef(pos: Vector3[np.double]) -> Vector3[np.double]:
    """Gravitation from ECEF position

    Note, gravitation does not include centrifugal effects in ECEF frame

    Equation (2.142) [@groves_principles_2013]"""
    rnorm2 = np.inner(pos, pos)
    rnorm2_inv = 1.0 / rnorm2
    tmp1 = 5.0 * pos[2] * pos[2] * rnorm2_inv
    tmp2 = (
        1.5
        * geode.EARTH_DYNAMICAL_J2
        * geode.EARTH_SEMIMAJOR_AXIS
        * geode.EARTH_SEMIMAJOR_AXIS
        * rnorm2_inv
    )
    tmp3 = -rnorm2_inv * np.sqrt(rnorm2_inv) * geode.EARTH_GRAVITATIONAL_FIELD
    return tmp3 * (pos + tmp2 * (np.array([1.0, 1.0, 3.0]) - tmp1) * pos)
