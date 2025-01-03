local Build(distribution, build_container) = {
  "kind": "pipeline",
  "type": "docker",
  "name": distribution,
  "steps": [
    {
      "name": "build packages",
      "image": build_container,
      "environment": {
        "DEBIAN_FRONTEND": "noninteractive",
        "DEB_BUILD_OPTIONS": "terse"
      },
      "commands": [
        "dpkg-buildpackage -uc -us -b -j$(nproc)"
      ]
    }
  ]
};

local Notification(dependencies) = {
  "kind": "pipeline",
  "name": "email-notification",
  "depends_on": dependencies,
  "trigger": {
    "status": [
        "failure",
        "success"
    ]
  },
  "steps": [
    {
      "name": "notify",
      "image": "drillster/drone-email",
      "settings": {
        "host": "mx.benfm.de",
        "from": "drone@benfm.de",
        "skip_verify": "true"
      },
      "when": {
        "status": [ "failure", "success" ]
      }
    }
  ]
};

[
  Build("ubuntu-jammy", "nx.benfm.de:5000/drone-container:22.04"),
  Build("ubuntu-noble", "nx.benfm.de:5000/drone-container:24.04"),
  Build("ubuntu-plucky", "nx.benfm.de:5000/drone-container:25.04"),
  Build("debian-trixie", "nx.benfm.de:5000/drone-container:trixie"),
  Notification(["ubuntu-jammy", "ubuntu-noble", "ubuntu-plucky", "debian-trixie"])
]
