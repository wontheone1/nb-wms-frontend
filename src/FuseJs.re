type t;

type options = {
  includeScore: bool,
  keys: array(string),
  useExtendedSearch: bool,
};

[@bs.new] [@bs.module "fuse.js"]
external createFuse: (array(Model.location), options) => t = "default";

type searchedLocation = {
  item: Model.location,
  refIndex: int,
  score: float,
};

type locationSearchResult = array(searchedLocation);

[@bs.send] external search: (t, string) => locationSearchResult = "search";

let fuseOptions: options = {
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
