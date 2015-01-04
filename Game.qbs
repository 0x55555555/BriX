import "../Eks/EksBuild" as Eks;

Eks.Library {
  name: "Game"
  toRoot: "Nomad"

  cpp.includePaths: base.concat([ "." ])

  files: [ "Game/**/*.h", "Game/**/*.cpp"]

  Depends { name: "cpp" }
  Depends { name: "ShiftCore" }
  Depends { name: "NomadCore" }
  Depends { name: "NomadEditor" }
  Depends { name: "NomadRenderer" }
}
