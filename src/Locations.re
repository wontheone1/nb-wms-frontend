module Ui = SemanticUi;

type location = Model.location;

type column =
  | Id
  | Description;

type sortDirection = Ui.Table.sortDirection;

[@react.component]
let make = (~searchQuery: string) => {
  let initialLocations: array(location) = [||];
  let (locations: array(location), setLocations) =
    React.useState(() => initialLocations);

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
      </Ui.Table.Row>
    </Ui.Table.Header>
    <Ui.Table.Body>
      {Belt.Array.keep(locations, (loc: location) =>
         if (searchQuery == "") {
           true;
         } else {
           loc.id == searchQuery || loc.desc == searchQuery;
         }
       )
       ->Belt.Array.map((loc: location) => {
           <Ui.Table.Row key={loc.id}>
             <Ui.Table.Cell> loc.id->React.string </Ui.Table.Cell>
             <Ui.Table.Cell> loc.desc->React.string </Ui.Table.Cell>
           </Ui.Table.Row>
         })
       ->React.array}
    </Ui.Table.Body>
  </Ui.Table>;
};
