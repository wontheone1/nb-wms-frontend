module Button = {
  [@bs.module "semantic-ui-react"] [@react.component]
  external make:
    (~children: React.element, ~onClick: ReactEvent.Mouse.t => unit=?) =>
    React.element =
    "Button";
};
