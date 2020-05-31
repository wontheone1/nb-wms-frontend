type t;

type options = {
  includeScore: bool,
  keys: array(string),
  useExtendedSearch: bool,
};

[@bs.new] [@bs.module "fuse.js"]
external createFuse: (array('a), options) => t = "default";

type searchedItem('a) = {
  item: 'a,
  refIndex: int,
  score: float,
};

[@bs.send] external search: (t, string) => array('a) = "search";

let locationFuseOptions: options = {
  // isCaseSensitive: false,
  includeScore: true,
  // shouldSort: true,
  // includeMatches: false,
  // findAllMatches: false,
  // minMatchCharLength: 1,
  // location: 0,
  // threshold: 0.6,
  // distance: 100,
  keys: [|"id", "desc"|],
  useExtendedSearch: true,
};

let itemFuseOptions: options = {
  includeScore: true,
  keys: [|"id", "name", "location"|],
  useExtendedSearch: true,
};
