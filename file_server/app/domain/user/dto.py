from typing import Optional
from pydantic import BaseModel

class UserDTO(BaseModel):
    id: int
    name: str
    email: str
    hashed_password: str

class UserUpdateDTO(BaseModel):
    name: Optional[str] = None
    email: Optional[str] = None

class UserCreateDTO(BaseModel):
    name: str
    email: str
    plain_password: str