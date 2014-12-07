import "Nomad/Eks/EksBuild" as Eks;

Eks.SubModule {
  name: "GameAll"
  toRoot: "Nomad"

  references: [
    "Nomad/Nomad.qbs",
    "Game.qbs",
  ]
}
