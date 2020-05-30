module Ui = SemanticUi;

type location = Model.location;

[@react.component]
let make = (~location: location) =>
  <Ui.Table.Row key={location.id}>
    <Ui.Table.Cell> location.id->React.string </Ui.Table.Cell>
    <Ui.Table.Cell> location.desc->React.string </Ui.Table.Cell>
    <Ui.Button onClick={_ => Firebase.deleteLocation(location.id)}>
      {j|삭제|j}->React.string
    </Ui.Button>
  </Ui.Table.Row>;
