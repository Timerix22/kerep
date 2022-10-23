# kprint
I don't really like printf function (and its variants), so i made safer and more convinient replacement.

| function | returns | arguments |
|----------|---------|-----------|
| kprint   | void/throw   | kprint_format, void*, kprint_format, void*... |
| ksprint  | Maybe<char*> | kprint_format, void*, kprint_format, void*... |
| kfprint  | Maybe<void>  | FILE*, kprint_format, void*, kprint_format, void*... |

## how to use it:
+ **format construction:**  
    ```
    kprint_format fmt= kprint_fgColor | kprint_bgColor | kprint_fdataFmt | flags | ktId;
    ```
    [more about `kprint_format`](kprint_format.md)
    + fgColor and bgColor can be set to change console output color
    + you should set dataFormat for `int`/`uint`/`float`/`char*` arguments and ktId for other types 
    + flags can be set to modify TypeDescriptor.toString() behavior
    + don't forget to set TypeDescriptor.toString when registering type, or kprint will crash

+ **using base type arguments:**   
    you can just put them into a function
    ```
    kprint(kprint_fmtHex | kprint_fmtUppercase | kprint_fmtWithPrefix, 255);
    ```
    output: 0xFF
+ **using other registered types:**  
    should be sent as pointers
    ```
    Maybe m=MaybeNull;
    kprint(kprint_fgBlue | kprint_fmtString, "Maybe: ", kprint_fgGreen | ktId_MaybePtr, &m);
    ```  
    output: <span style="color:blue">Maybe:</span> <span style="color:lightgreen">{value={0, ktId_Null}}</span>