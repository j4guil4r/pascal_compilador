import os
import subprocess
from pathlib import Path

# Configuración específica para CLion
TEST_DIR = "test/test"                # Carpeta con tests .pas
ASM_DIR = "test/asm"                  # Carpeta para guardar .s
COMPILER_EXE = "cmake-build-debug/pascal_compilador.exe"  # Ruta exacta a tu compilador

def run_tests():
    """Ejecuta todas las pruebas .pas con el compilador de CLion"""
    print(f"🔍 Buscando tests en {TEST_DIR}")

    # Crear carpeta ASM si no existe
    os.makedirs(ASM_DIR, exist_ok=True)

    # Procesar cada archivo .pas
    for test_file in Path(TEST_DIR).glob("*.pas"):
        asm_file = Path(ASM_DIR) / f"{test_file.stem}.s"

        print(f"\n📄 Procesando: {test_file.name}")
        print(f"   🎯 Output: {asm_file}")

        try:
            # Ejecutar compilador y guardar salida
            with open(asm_file, "w") as f:
                subprocess.run([COMPILER_EXE, str(test_file)], stdout=f, check=True)

            # Verificar que se generó el archivo
            if asm_file.exists():
                print(f"   ✅ Generado ({asm_file.stat().st_size} bytes)")
            else:
                print("   ❌ Error: No se generó el archivo")
        except subprocess.CalledProcessError as e:
            print(f"   ❌ Error en compilación (código {e.returncode})")
        except Exception as e:
            print(f"   🚨 Error inesperado: {str(e)}")

if __name__ == "__main__":
    # Verificar que existe el compilador
    if not Path(COMPILER_EXE).exists():
        print(f"❌ Error: No se encontró {COMPILER_EXE}")
        print("Ejecuta CLion primero para compilar el proyecto")
        exit(1)

    run_tests()
    print("\n✨ Proceso completado")