Dim oFSO
Set oFSO = CreateObject("Scripting.FileSystemObject")

title = InputBox("Please enter the project title", "Project title")
oFSO.CopyFolder "_template", title
oFSO.MoveFile title+"\_template.uvproj", title+"\"+title+".uvproj"
oFSO.MoveFile title+"\_template.c", title+"\"+title+".c"

FindAndReplace title+"\.vscode\tasks.bat", "CHANGE_THIS_TO_MATCH_YOUR_PROJECT", title
FindAndReplace title+"\"+title+".uvproj", "_template", title

function FindAndReplace(strFilename, strFind, strReplace)
    Set inputFile = CreateObject("Scripting.FileSystemObject").OpenTextFile(strFilename, 1)
    strInputFile = inputFile.ReadAll
    inputFile.Close
    Set inputFile = Nothing
    Set outputFile = CreateObject("Scripting.FileSystemObject").OpenTextFile(strFilename,2,true)
    outputFile.Write Replace(strInputFile, strFind, strReplace)
    outputFile.Close
    Set outputFile = Nothing
end function 
