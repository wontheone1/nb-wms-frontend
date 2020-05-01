// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());

[@react.component]
let make = () => {
  let (locationIdValue, setLocationIdValue) = React.useState(() => "");
  let (descValue, setDescValue) = React.useState(() => "");
  <form
    id="locationForm"
    onSubmit={e => {
      ReactEvent.Form.preventDefault(e);
      Firebase.createLocation(locationIdValue, descValue);
      setLocationIdValue(_ => "");
      setDescValue(_ => "");
    }}>
    <label>
      {React.string("Location ID: ")}
      <input
        id="locationIdInput"
        type_="text"
        value=locationIdValue
        onChange={(event: ReactEvent.Form.t) => {
          ReactEvent.Form.persist(event);
          setLocationIdValue(_ => ReactEvent.Form.target(event)##value);
        }}
      />
    </label>
    <label>
      {React.string("Description: ")}
      <input
        id="locationDescriptionInput"
        type_="text"
        value=descValue
        onChange={(event: ReactEvent.Form.t) => {
          ReactEvent.Form.persist(event);
          setDescValue(_ => ReactEvent.Form.target(event)##value);
        }}
      />
    </label>
    <input type_="submit" value="Submit" />
  </form>;
};
