{ pkgs }: {
  deps = [
    pkgs.gcc
    pkgs.xsimd
    pkgs.pkg-config
    pkgs.libxcrypt
    pkgs.bashInteractive
    pkgs.nodePackages.bash-language-server
    pkgs.man
    pkgs.boost
    pkgs.gnat
  ];
}