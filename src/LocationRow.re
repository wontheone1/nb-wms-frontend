module Ui = SemanticUi;

type location = Model.location;
type editing =
  | Editing
  | NotEditing;

[@react.component]
let make = (~location: location) => {
  let (editing, setEditing) = React.useState(() => NotEditing);
  let (newDesc, setNewDesc) = React.useState(() => location.desc);
  <Ui.Table.Row key={location.id}>
    <Ui.Table.Cell> location.id->React.string </Ui.Table.Cell>
    <Ui.Table.Cell> location.desc->React.string </Ui.Table.Cell>
    {switch (editing) {
     | Editing =>
       <Ui.Table.Cell>
         <Ui.Input
           label={basic: true, content: {j|위치 아이디|j}}
           onChange={(event: ReactEvent.Form.t) => {
             let value = ReactEvent.Form.target(event)##value;
             setNewDesc(_ => value);
           }}
           placeholder={j|새로운 세부사항 입력|j}
           value=newDesc
         />
         <Ui.Button
           onClick={_ => {
             setEditing(_ => NotEditing);
             Firebase.createLocation(location.id, newDesc);
           }}>
           {j|편집완료|j}->React.string
         </Ui.Button>
       </Ui.Table.Cell>
     | NotEditing =>
       <Ui.Table.Cell>
         <Ui.Button onClick={_ => setEditing(_ => Editing)}>
           {j|세부사항 편집|j}->React.string
         </Ui.Button>
       </Ui.Table.Cell>
     }}
    <Ui.Table.Cell>
      <Ui.Button onClick={_ => Firebase.deleteLocation(location.id)}>
        {j|삭제|j}->React.string
      </Ui.Button>
    </Ui.Table.Cell>
  </Ui.Table.Row>;
};
