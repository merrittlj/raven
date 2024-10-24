let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.05";
  nixpkgs-unstable = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-unstable";
  pkgs = import nixpkgs { config = {}; overlays = []; };
  unstable = import nixpkgs-unstable { config = {}; overlays = []; };
in
pkgs.mkShellNoCC {
  packages = with pkgs; [
    cmake
    openocd
    picocom
    doxygen
    newlib
    newlib-nano
  ]++ [ unstable.gcc-arm-embedded-13 ]; # Stable gdb has deprecated python links
}
