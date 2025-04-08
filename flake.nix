{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    jlink-pack.url = "github:prtzl/jlink-nix"; # jlink debugger support
  };

  outputs = inputs:
    with inputs;
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      stdenv = pkgs.stdenv;
      jlink = jlink-pack.defaultPackage.${system};
      
      flash-stlink = pkgs.writeShellApplication {
        name = "flash-stlink";
        text = "st-flash --reset write ./Debug/bootloaderfinal.bin 0x08000000";
        runtimeInputs = [ pkgs.stlink ];
      };
      
      jlink-script = pkgs.writeTextFile {
        name = "jlink-script";
        text = ''
          device 'STM32L4A6ZG'
          si 1
          speed 4000
          loadfile ./Debug/bootloaderfinal.elf,0x00000000
          r
          g
          qc
        '';
      };
      
      flash-jlink = pkgs.writeShellApplication {
        name = "flash-jlink";
        text = "JLinkExe -commanderscript ${jlink-script}";
        runtimeInputs = [ jlink ];
      };
    in {
      inherit flash-jlink flash-stlink;

      defaultPackage.${system} = flash-stlink;

      devShell.${system} = pkgs.mkShell {
        nativeBuildInputs = ([ ])
          ++ [ pkgs.clang-tools jlink pkgs.stlink pkgs.dos2unix ];
        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.llvmPackages_12.llvm ];
      };
    };
}
