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
      label={basic: true, content: {j|위치 아이디|j}}
      onChange={(event: ReactEvent.Form.t) => {
        let value = ReactEvent.Form.target(event)##value;
        setLocationIdValue(_ => value);
      }}
      placeholder={j|위치 아이디 입력|j}
      value=locationIdValue
    />
    <Ui.Input
      action={
        content: {j|추가|j},
        onClick: e =>
          {ReactEvent.Mouse.preventDefault(e);
           Firebase.createOrEditLocation(locationIdValue, descValue);
           setLocationIdValue(_ => "");
           setDescValue(_ => "")},
      }
      id="locationDescriptionInput"
      label={basic: true, content: {j|세부 사항|j}}
      onChange={(event: ReactEvent.Form.t) => {
        let value = ReactEvent.Form.target(event)##value;
        setDescValue(_ => value);
      }}
      placeholder={j|세부사항 입력|j}
      value=descValue
    />
  </form>;
};
