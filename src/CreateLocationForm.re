// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());

let handleSubmit = desc => Firebase.createLocation("abcde", desc);

[@react.component]
let make = () => {
  let (descValue, setDescValue) = React.useState(() => "");
  <form
    id="descriptionForm"
    onSubmit={e => {
      ReactEvent.Form.preventDefault(e);
      handleSubmit(descValue);
    }}>
    <label>
      {React.string("Description: ")}
      <input
        id="descriptionFormInput"
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
