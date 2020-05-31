module Ui = SemanticUi;
module M = Model;

type column =
  | Id
  | Name
  | Location;

type sortDirection = Ui.Table.sortDirection;

[@react.component]
let make = (~items, ~searchQuery: string, ~setItems) => {
  let (sortedByColumn, setSortedByColumn) = React.useState(() => Id);
  let (direction, setDirection) = React.useState(() => Ui.Table.Ascending);
  let handleSort = (clickedColumn: column, _: ReactEvent.Mouse.t) =>
    if (sortedByColumn != clickedColumn) {
      setSortedByColumn(_ => clickedColumn);
      setDirection(_ => Ui.Table.Ascending);
      setItems(oldItems =>
        Belt.SortArray.stableSortBy(oldItems, (itemA: M.item, itemB: M.item) =>
          switch (clickedColumn) {
          | Id => compare(itemA.articleId, itemB.articleId)
          | Name => compare(itemA.name, itemB.name)
          | Location => compare(itemA.location, itemB.location)
          }
        )
      );
    } else {
      setDirection(oldDirection =>
        switch (oldDirection) {
        | Ui.Table.Ascending => Ui.Table.Descending
        | Ui.Table.Descending => Ui.Table.Ascending
        | Ui.Table.NoDirection => Ui.Table.Ascending
        }
      );
      setItems(oldElements => Belt.Array.reverse(oldElements));
    };

  <Ui.Table sortable=true celled=true fixed=true>
    <Ui.Table.Header>
      <Ui.Table.Row>
        <Ui.Table.HeaderCell
          sorted={sortedByColumn == Id ? direction : Ui.Table.NoDirection}
          onClick={handleSort(Id)}>
          {j|제품 아이디|j}->React.string
        </Ui.Table.HeaderCell>
        <Ui.Table.HeaderCell
          sorted={sortedByColumn == Name ? direction : Ui.Table.NoDirection}
          onClick={handleSort(Name)}>
          {j|제품 이름|j}->React.string
        </Ui.Table.HeaderCell>
        <Ui.Table.HeaderCell
          sorted={
            sortedByColumn == Location ? direction : Ui.Table.NoDirection
          }
          onClick={handleSort(Location)}>
          {j|제품 위치 아이디|j}->React.string
        </Ui.Table.HeaderCell>
        <Ui.Table.HeaderCell> {j|삭제|j}->React.string </Ui.Table.HeaderCell>
      </Ui.Table.Row>
    </Ui.Table.Header>
    <Ui.Table.Body>
      {let filteredItems: array(M.item) =
         switch (searchQuery) {
         | "" => items
         | _ =>
           let result =
             FuseJs.createFuse(items, FuseJs.itemFuseOptions)
             ->FuseJs.search(searchQuery);

           Js.log2("Search result", result);

           Belt.Array.map(
             result,
             (searchedItem: FuseJs.searchedItem(M.item)) => {
               let loc: M.item = {
                 articleId: searchedItem.item.articleId,
                 name: searchedItem.item.name,
                 location: searchedItem.item.location,
               };
               loc;
             },
           );
         };

       filteredItems
       ->Belt.Array.map((item: M.item) => <ItemRow item />)
       ->React.array}
    </Ui.Table.Body>
  </Ui.Table>;
};
