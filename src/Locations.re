module Ui = SemanticUi;

type location = Model.location;

type sortDirection =
  | Ascending
  | Descending;

type column =
  | Id
  | Description;

let sortDirectionToStringOption = direction => {
  switch (direction) {
  | Some(Ascending) => Some("ascending")
  | Some(Descending) => Some("descending")
  | None => None
  };
};

[@react.component]
let make = (~signedIn) => {
  let initialLocations: array(location) = [||];
  let (locations: array(location), setLocations) =
    React.useState(() => initialLocations);

  let (sortedByColumn, setSortedByColumn) = React.useState(() => Id);
  let (direction, setDirection) = React.useState(() => Some(Ascending));

  let handleSort = (clickedColumn: column, _: ReactEvent.Mouse.t) =>
    if (sortedByColumn != clickedColumn) {
      setSortedByColumn(_ => clickedColumn);
      setDirection(_ => Some(Ascending));
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
        | Some(Ascending) => Some(Descending)
        | Some(Descending) => Some(Ascending)
        | None => Some(Ascending)
        }
      );
      setLocations(oldLocations => Belt.Array.reverse(oldLocations));
    };

  React.useEffect0(() => {
    Firebase.readLocations(setLocations);
    None;
  });

  signedIn
    ? <Ui.Table sortable=true celled=true fixed=true>
        <Ui.Table.Header>
          <Ui.Table.Row>
            <Ui.Table.HeaderCell
              sorted={
                sortedByColumn == Id
                  ? Js.Nullable.fromOption(
                      sortDirectionToStringOption(direction),
                    )
                  : Js.Nullable.null
              }
              onClick={handleSort(Id)}>
              "ID"->React.string
            </Ui.Table.HeaderCell>
            <Ui.Table.HeaderCell
              sorted={
                sortedByColumn == Description
                  ? Js.Nullable.fromOption(
                      sortDirectionToStringOption(direction),
                    )
                  : Js.Nullable.null
              }
              onClick={handleSort(Description)}>
              "Description"->React.string
            </Ui.Table.HeaderCell>
          </Ui.Table.Row>
        </Ui.Table.Header>
        <Ui.Table.Body>
          {Array.map(
             (loc: location) => {
               <Ui.Table.Row key={loc.id}>
                 <Ui.Table.Cell> loc.id->React.string </Ui.Table.Cell>
                 <Ui.Table.Cell> loc.desc->React.string </Ui.Table.Cell>
               </Ui.Table.Row>
             },
             locations,
           )
           ->React.array}
        </Ui.Table.Body>
      </Ui.Table>
    : <div />;
};
