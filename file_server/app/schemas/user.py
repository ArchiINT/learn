
from typing import Optional

from pydantic import BaseModel, ConfigDict


class UserCreateSchema(BaseModel):
    name: str
    email: str
    plain_password: str

class UserResponseSchema(BaseModel):
    id: int
    name: str
    email: str
    model_config = ConfigDict(from_attributes=True) # Pydantic should can read Objects atribute to return json 

class UserUpdateSchema(BaseModel):
    name: Optional[str] = None
    email: Optional[str] = None