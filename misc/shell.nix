let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.05";
  nixpkgs-unstable = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-unstable";
  pkgs = import nixpkgs { config = {}; overlays = []; };
  unstable = import nixpkgs-unstable { config = {}; overlays = []; };
in
pkgs.mkShellNoCC {
  packages = with pkgs; [
    imagemagick
    pngquant
    python311Packages.pillow
    python311Packages.configargparse
    python311Packages.numpy
    python311Packages.pypng
    python311Packages.lz4
  ]++ [  ];
}
