# Configuración
$COMPILER = ".\cmake-build-debug\pascal_compilador.exe"
$TEST_DIR = ".\test\test"
$ASM_DIR = ".\test\asm"

# Crear directorio asm si no existe
if (-not (Test-Path $ASM_DIR)) {
    New-Item -ItemType Directory -Path $ASM_DIR | Out-Null
}

# Verificar si el compilador existe
if (-not (Test-Path $COMPILER)) {
    Write-Host "Error: No se encontró el compilador en $COMPILER" -ForegroundColor Red
    exit 1
}

Write-Host "`nIniciando generación de ASM..." -ForegroundColor Cyan

# Procesar todos los tests .pas
Get-ChildItem -Path "$TEST_DIR\*.pas" | ForEach-Object {
    $asm_file = "$ASM_DIR\$($_.BaseName).s"
    Write-Host "  Procesando $($_.Name) -> $($asm_file)"

    # Ejecutar el compilador y guardar salida en .s
    & $COMPILER $_.FullName > $asm_file

    # Verificar éxito
    if (Test-Path -Path $asm_file -PathType Leaf) {
        $fileSize = (Get-Item $asm_file).Length
        Write-Host "    [OK] Generado ($fileSize bytes)" -ForegroundColor Green
    } else {
        Write-Host "    [ERROR] Falló la generación" -ForegroundColor Red
    }
}

Write-Host "`n¡Proceso completado! Archivos ASM en: $ASM_DIR" -ForegroundColor Green