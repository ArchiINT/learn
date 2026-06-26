from abc import ABC, abstractmethod
from typing import Generic, List
from typing_extensions import Generic, TypeVar


TEntity = TypeVar('TEntity')
TCreateDTO= TypeVar("TCreateDTO")
TUpdateDTO = TypeVar("TUpdateDTO")
TId = TypeVar("TId")

class AbstractRepository(Generic[TEntity, TId, TCreateDTO, TUpdateDTO], ABC):

    @abstractmethod
    def get(entity_id: TId) -> TEntity:
        ...

    @abstractmethod
    def get_list(limit: int = 100, offset: int = 10) -> List[TEntity]:
        ...

    @abstractmethod
    def create(dto: TCreateDTO) -> TEntity:
        ...

    @abstractmethod
    def update(dto: TUpdateDTO) -> TEntity:
        ...

    @abstractmethod
    def delete(entity_id: TId) -> None:
        ...

        