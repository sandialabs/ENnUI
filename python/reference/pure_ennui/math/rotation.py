import numpy as np
from numpy.linalg import norm as norm

__all__ = ["R3_to_so3", "R3_to_SO3", "normalize_SO3_Groves"]


def R3_to_so3(theta):
    """$R^3 \rightarrow so(3)$"""
    skewsymm = np.array(
        [
            [0, -theta[2], theta[1]],
            [theta[2], 0, -theta[0]],
            [-theta[1], theta[0], 0],
        ]
    )
    return skewsymm


def R3_to_SO3(theta):
    """Matrix exponentials computed directly"""
    #  Using sinc to avoid divide by 0. numpy uses normalized sinc (ick!)
    thetanorm = norm(theta) / np.pi
    f1 = np.sinc(thetanorm)
    f2 = 0.5 * np.sinc(0.5 * thetanorm) ** 2
    Omega = R3_to_so3(theta)
    M = np.eye(3) + f1 * Omega + f2 * Omega @ Omega
    return M


def normalize_SO3_Groves(R):
    """Matrix normalization using Grove's approximation"""

    d01 = np.inner(R[0, :], R[1, :])
    d02 = np.inner(R[0, :], R[2, :])
    d12 = np.inner(R[1, :], R[2, :])
    rslt = np.ndarray((3, 3))
    rslt[0, :] = R[0, :] - 0.5 * d01 * R[1, :] - 0.5 * d02 * R[2, :]
    rslt[1, :] = -0.5 * d01 * R[0, :] + R[1, :] - 0.5 * d12 * R[2, :]
    rslt[2, :] = -0.5 * d02 * R[0, :] - 0.5 * d12 * R[1, :] + R[2, :]
    for i in range(3):
        rslt[i, :] = rslt[i, :] / np.linalg.norm(rslt[i, :])

    return rslt
