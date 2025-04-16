from typing import Annotated, Literal, TypeVar
import numpy as np
import numpy.typing as npt

DType = TypeVar("DType", bound=np.generic)

Vector3 = Annotated[npt.NDArray[DType], Literal[3]]
Vector4 = Annotated[npt.NDArray[DType], Literal[4]]
Matrix3x3 = Annotated[npt.NDArray[DType], Literal[3, 3]]

__all__ = ["DType", "Vector3", "Vector4", "Matrix3x3"]
