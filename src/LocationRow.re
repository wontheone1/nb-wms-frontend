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
         <form>
           <Ui.Input
             action={
               content: {j|편집완료|j},
               onClick: e =>
                 {setEditing(_ => NotEditing);
                  Firebase.createOrEditLocation(location.id, newDesc)},
             }
             onChange={(event: ReactEvent.Form.t) => {
               let value = ReactEvent.Form.target(event)##value;
               setNewDesc(_ => value);
             }}
             placeholder={j|새로운 세부사항 입력|j}
             value=newDesc
           />
         </form>
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
