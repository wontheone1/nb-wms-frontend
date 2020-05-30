module Ui = SemanticUi;

type location = Model.location;

type column =
  | Id
  | Description;

type sortDirection = Ui.Table.sortDirection;

[@react.component]
let make = (~locations, ~searchQuery: string, ~setLocations) => {
  let (sortedByColumn, setSortedByColumn) = React.useState(() => Id);
  let (direction, setDirection) = React.useState(() => Ui.Table.Ascending);
  let handleSort = (clickedColumn: column, _: ReactEvent.Mouse.t) =>
    if (sortedByColumn != clickedColumn) {
      setSortedByColumn(_ => clickedColumn);
      setDirection(_ => Ui.Table.Ascending);
      setLocations(oldLocations =>
        Belt.SortArray.stableSortBy(
          oldLocations, (locA: location, locB: location) =>
          switch (clickedColumn) {
          | Id => compare(locA.id, locB.id)
          | Description => compare(locA.desc, locB.desc)
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
      setLocations(oldLocations => Belt.Array.reverse(oldLocations));
    };

  React.useEffect0(() => {
    Firebase.readLocations(setLocations);
    None;
  });

  <Ui.Table sortable=true celled=true fixed=true>
    <Ui.Table.Header>
      <Ui.Table.Row>
        <Ui.Table.HeaderCell
          sorted={sortedByColumn == Id ? direction : Ui.Table.NoDirection}
          onClick={handleSort(Id)}>
          {j|위치 아이디|j}->React.string
        </Ui.Table.HeaderCell>
        <Ui.Table.HeaderCell
          sorted={
            sortedByColumn == Description ? direction : Ui.Table.NoDirection
          }
          onClick={handleSort(Description)}>
          {j|세부사항|j}->React.string
        </Ui.Table.HeaderCell>
        <Ui.Table.HeaderCell> {j|삭제|j}->React.string </Ui.Table.HeaderCell>
      </Ui.Table.Row>
    </Ui.Table.Header>
    <Ui.Table.Body>
      {let filteredLocations: array(location) =
         switch (searchQuery) {
         | "" => locations
         | _ =>
           let result =
             FuseJs.createFuse(locations, FuseJs.fuseOptions)
             ->FuseJs.search(searchQuery);

           Js.log2("Search result", result);

           Belt.Array.map(
             result,
             (searchedLocation: FuseJs.searchedLocation) => {
               let loc: location = {
                 id: searchedLocation.item.id,
                 desc: searchedLocation.item.desc,
               };
               loc;
             },
           );
         };

       filteredLocations
       ->Belt.Array.map((location: location) => <LocationRow location />)
       ->React.array}
    </Ui.Table.Body>
  </Ui.Table>;
};
