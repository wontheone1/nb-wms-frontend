let hiddenDisplayStyle = ReactDOMRe.Style.make(~display="none", ());
let signinPlaceholder = ReactDOMRe.Style.make();

[@react.component]
let make = (~signedIn) =>
  <div
    style={signedIn ? hiddenDisplayStyle : signinPlaceholder}
    id="signin-placeholder"
  />;
