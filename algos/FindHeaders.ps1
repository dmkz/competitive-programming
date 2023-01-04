$FileName = "headers.txt"
if (Test-Path $FileName) {
    Remove-Item $FileName;
}
Get-ChildItem -Path .\ -Filter *.hpp -Recurse -File -Name| ForEach-Object {
    Write-Output "$_" | Out-File -encoding ASCII -FilePath $FileName -Append;
}