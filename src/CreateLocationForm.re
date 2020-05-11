module Ui = SemanticUi;

// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());

[@react.component]
let make = () => {
  let (locationIdValue, setLocationIdValue) = React.useState(() => "");
  let (descValue, setDescValue) = React.useState(() => "");
  <form id="locationForm">
    <Ui.Input
      id="locationIdInput"
      label={basic: true, content: "Id"}
      onChange={(event: ReactEvent.Form.t) => {
        let value = ReactEvent.Form.target(event)##value;
        setLocationIdValue(_ => value);
      }}
      placeholder="Enter barcode"
      value=locationIdValue
    />
    <Ui.Input
      action={
        content: "Submit",
        onClick: e =>
          {ReactEvent.Mouse.preventDefault(e);
           Firebase.createLocation(locationIdValue, descValue);
           setLocationIdValue(_ => "");
           setDescValue(_ => "")},
      }
      id="locationDescriptionInput"
      label={basic: true, content: "Description"}
      onChange={(event: ReactEvent.Form.t) => {
        let value = ReactEvent.Form.target(event)##value;
        setDescValue(_ => value);
      }}
      placeholder="Enter description"
      value=descValue
    />
  </form>;
};
