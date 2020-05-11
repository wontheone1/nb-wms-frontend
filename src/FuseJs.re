type t;

type options = {
  includeScore: bool,
  keys: array(string),
  useExtendedSearch: bool,
};

[@bs.new] [@bs.module "fuse.js"]
external createFuse: (array(Model.location), options) => t = "default";

[@bs.send] external search: (t, string) => array(Model.location) = "search";

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

let locations: array(Model.location) = [|
  {id: "Old Man's War", desc: "John Scalzi"},
  {id: "The Lock Artist", desc: "English"},
|];

let fuse = createFuse(locations, fuseOptions);

let result = search(fuse, "engsh");
