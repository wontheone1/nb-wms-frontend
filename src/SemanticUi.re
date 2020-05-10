module Button = {
  [@bs.module "semantic-ui-react"] [@react.component]
  external make:
    (~children: React.element, ~onClick: ReactEvent.Mouse.t => unit=?) =>
    React.element =
    "Button";
};

module Input = {
  [@bs.module "semantic-ui-react"] [@react.component]
  external make:
    (~children: React.element=?, ~icon: string=?, ~placeholder: string=?) =>
    React.element =
    "Input";
};

module Menu = {
  [@bs.module "semantic-ui-react"] [@react.component]
  external make:
    (~children: React.element, ~secondary: bool=?) => React.element =
    "Menu";

  module Item = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Menu"] [@react.component]
    external make:
      (
        ~active: bool=?,
        ~children: React.element=?,
        ~name: string=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "Item";
  };

  module Menu = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Menu"] [@react.component]
    external make:
      (~children: React.element, ~position: string) => React.element =
      "Menu";
  };
};

module Table = {
  [@bs.module "semantic-ui-react"] [@react.component]
  external make:
    (
      ~children: React.element,
      ~sortable: bool,
      ~celled: bool,
      ~fixed: bool,
      ~onClick: ReactEvent.Mouse.t => unit=?
    ) =>
    React.element =
    "Table";

  module Header = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Table"] [@react.component]
    external make:
      (
        ~children: React.element,
        ~sortable: bool=?,
        ~celled: bool=?,
        ~fixed: bool=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "Header";
  };

  module Row = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Table"] [@react.component]
    external make:
      (
        ~children: React.element,
        ~sortable: bool=?,
        ~celled: bool=?,
        ~fixed: bool=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "Row";
  };

  type sortDirection =
    | Ascending
    | Descending
    | NoDirection;

  module HeaderCell = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Table"] [@react.component]
    external make:
      (
        ~children: React.element,
        ~sorted: sortDirection=?,
        ~celled: bool=?,
        ~fixed: bool=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "HeaderCell";
  };

  module Body = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Table"] [@react.component]
    external make:
      (
        ~children: React.element,
        ~sorted: Js.Nullable.t(string)=?,
        ~celled: bool=?,
        ~fixed: bool=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "Body";
  };

  module Cell = {
    [@bs.module "semantic-ui-react"] [@bs.scope "Table"] [@react.component]
    external make:
      (
        ~children: React.element,
        ~sorted: Js.Nullable.t(string)=?,
        ~celled: bool=?,
        ~fixed: bool=?,
        ~onClick: ReactEvent.Mouse.t => unit=?
      ) =>
      React.element =
      "Cell";
  };
};
