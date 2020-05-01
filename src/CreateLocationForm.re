// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());

[@react.component]
let make = () =>
  <button
    style=leftButtonStyle
    onClick={_event =>
      Firebase.createLocation("abcde", "shelf level 1/section 1")
    }>
    {React.string("Create/Update Location")}
  </button>;
