module Ui = SemanticUi;
module M = Model;

[@react.component]
let make = (~item: M.item) => {
  <Ui.Table.Row key={item.articleId}>
    <Ui.Table.Cell> item.articleId->React.string </Ui.Table.Cell>
    <Ui.Table.Cell> item.name->React.string </Ui.Table.Cell>
    <Ui.Table.Cell> item.location->React.string </Ui.Table.Cell>
    <Ui.Table.Cell>
      <Ui.Button onClick={_ => ()}> {j|삭제|j}->React.string </Ui.Button>
    </Ui.Table.Cell>
  </Ui.Table.Row>;
};
