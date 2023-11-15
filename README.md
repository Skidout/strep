# String Replace

### A replacement for old, dated & unintuitive *NIX text tools.

###### Most of the options are currently untested, but should work. I'll be testing the options thoroughly over the next little while, so I'll be sure to find any bugs.

#### Building

Dependencies: clang, llvm, libc++, lld

Command: "clang++ -stdlib=libc++ -std=c++17 -fuse-ld=lld -Ofast strep.cpp -o strep"

#### Possible Uses

Strep can be used for most things text-related outside of a text editor. If you have a large document or text file that needs to be processed, or if you want to filter a log file, or maybe even translate one programming language to another, & more, you can use Strep. It is generally expected that Strep will be used in a graphical environment with a terminal emulator, so it is written around this environment, but it can still be used within a text-only environment or script.

#### Options

-f[ile]
File to use as input, by default write back to file unless -p or -o
<string>

-p[ipe]
Output to STDOUT when used with -f
(toggle)

-o[utput]
New output file. Will always output.
<string>

Input is taken via STDIN by default.
-f will cause the program to take input from the specified file, and output to it if -o or -p are not selected.
-o will cause the program to output to the specified file.
-p will cause the program to output to STDOUT.

You can specify multiple parameters by adding a comma at the end, for example "replace this, and this" or "100, 150, 250".
When you can specify <int-int>, it means that all numbers including and between the numbers will be specified.
(toggle) means that there is no parameter to be specified, as the option toggles something on by itself.
Line count starts at 1, not 0.
Unicode characters will count as more than one character if they are not in ascii, emojis, etc. Only applies to options that rely on character numbers.
The formatting like t[his] is not usable, it is only meant to explain the option to provide a greater understanding.

The options are not listed here in the order they are checked by the program. List of options in order available below.

-d[elete]
Delete patterns.
<string>

    f
    Delete the first occurence of a pattern.
    <string>
    
    n
    Delete everything on a line but a pattern from a line containing the pattern.
    <string>
    
    l
    Delete lines by line numbers.
    <int>/<int-int>
    
    a
    Delete all (truncate) after a pattern.
    <string>
    
    b
    Delete all of a line up until a pattern.
    <string>
    
    t
    Delete all trailing whitespace and tab characters.
    (toggle)
    
    fn
    Delete everything on a line but a pattern from a line containing the pattern once.
    <string>
    
    ln
    Delete every line not specified.
    <int>/<int-int>
    
    lp
    Delete lines that contain a pattern.
    <string>
    
    af
    Delete all (truncate) after a pattern once.
    <string>
    
    a#
    Truncate after after a number of characters.
    <int>
    
    bf
    Delete all of a line up until a pattern once.
    <string>
    
    b#
    Delete after a number of characters from the beginning of the line.
    <int>
    
    lpn
    Delete lines that don't contain a pattern.
    <string>
    
    lpf
    Delete first line matching pattern
    <string>
    
    af#
    Truncate after a certain number of characters once.
    <int>
    
    bf#
    Delete after a number of characters from the beginning of a line once.
    <int>
    
    lpfn
    Delete lines until a pattern occurs
    <string>

-i[nsert]
Insert text after a pattern. First put the pattern, then the text.
<string> <string>

    a
    Append something to a line that contains a pattern.
    <string> <string>
    
    b
    Insert text before a pattern.
    <string> <string>
    
    f
    Insert text after the first occurence of a pattern.
    <string> <string>
    
    l
    Insert a line after specified line numbers.
    <string> <int>/<int-int>
    
    af
    Append text to the first line that contains a pattern.
    <string> <string>
    
    al
    Append text to specified lines.
    <string> <int>/<int-int>
    
    an
    Append text to the end of every line that doesn't contain a pattern.
    <string> <string>
    
    bf
    Insert text before the first occurence of a pattern.
    <string> <string>
    
    bp
    Insert text at the start of a line that matches a pattern
    <string> <string>
    
    bl
    Insert text at the beginning of specified lines.
    <string> <int>/<int-int>
    
    ln
    Insert a line after every line not specified.
    <string> <int>/<int-int>
    
    lp
    Insert a line after a line contains a pattern.
    <string> <string>
    
    afn
    Append text to the first line not containing a pattern.
    <string> <string>
    
    aln
    Append text to every line not specified.
    <string> <int>/<int-int>
    
    blp
    Insert a line before a line containing a pattern.
    <string> <string>
    
    bln
    Insert a line before every line not specified.
    <string> <int>/<int-int>
    
    bpn
    Insert text at the start of a line that doesn't contain a pattern.
    <string> <string>
    
    bfn
    Insert text at the start of a line that doesn't contain a pattern once.
    <string> <string>
    
    bpf
    Insert text at the start of a line that contains a pattern once.
    <string> <string>
    
    lpn
    Insert a line after a line that doesn't contain a pattern.
    <string> <string>
    
    lpf
    Insert a line after the first occurence of a pattern in a line.
    <string> <string>
    
    blpf
    Insert a line before a line containing a pattern once.
    <string> <string>
    
    bpfn
    Insert text at the start of a line that doesn't contain a pattern once.
    <string> <string>
    
    lpfn
    Insert a line after a line that doesn't contain a pattern once.
    <string> <string>
    
    blpfn
    Insert a line before a line not containing a pattern once.
    <string> <string>

-c[ut]
Cut the file after a pattern. File names are formatted as <original name>-#, with the first being 1, & no 0 padding.
<string>

    n
    Cut after lines that don't contain a pattern.
    <string>
    
    b
    Cut before a line containing a pattern.
    <string>
    
    f
    Cut after first occurence of a pattern.
    <string>
    
    l
    Cut after lines by number.
    <int>
    
    #
    Cut after every ### lines.
    <int>
    
    ln
    Cut after every line not specified.
    <int>
    
    fn
    Cut after the first line that doesn't contain a pattern.
    <string>
    
    bn
    Cut before lines not containing a pattern.
    <string>
    
    bf
    Cut before line where a pattern is found once.
    <string>
    
    b#
    Cut before every ### lines.
    <int>
    
    p#
    Cut after the number of times a pattern is found reaches a limit.
    <string> <int>
    
    bp#
    Cut before the number of times a pattern is found reaches a limit.
    <string> <int>
    
    bn#
    Cut before number of lines not containing a pattern reaches a limit.
    <string> <int>
    
    bfn
    Cut before a line where a pattern is not found once.
    <string>
    
    pf#
    Cut the after the number of times a pattern is found reaches a limit once.
    <string> <int>

-s[plit]
Split a line (insert newline) after a pattern.
<string>

    b
    Split before a pattern.
    <string>
    
    f
    Split after the first occurence of a pattern.
    <string>
    
    t
    Split after total count of a pattern reaches a limit
    <string> <int>
    
    #
    Split after a limit of characters on a line.
    <int>
    
    bt
    Split before total count of a pattern reaches a limit.
    <string> <int>
    
    f#
    Split after a limit of characters on a line once.
    <int>
    
    tf
    Split the first time a total count of a pattern reaches a limit.
    <string> <int>
    
    btf
    Split before a pattern reaches a limit once.
    <string> <int>

-m[erge]
Merge multiple text files. Optionally operate on files being merged by specifying "-oom".
<file>

    l
    Merge file after specified lines in the input.
    <file> <int>
    
    p
    Insert a file after lines containing a pattern.
    <file> <string>
    
    pf
    Insert a file after lines containing a pattern once.
    <file> <string>
    
    bl
    Merge file before specified lines in the input.
    <file> <int>
    
    bp
    Merge file before lines containing a pattern.
    <file> <string>
    
    bpf
    Merge file before the first line containing a pattern.
    <file> <string>

-r[eplace]
Replace patters with text. Substring first, the replacing pattern second.
<string> <string>

    f
    Only replace the first occurence of a pattern.
    <string> <string>
    
    l
    Replace lines with other lines.
    <int>/<int-int> <string>
    
    ln
    Replace every line not specified with another line.
    <int>/<int-int> <string>
    
    lp
    Replace lines containing a pattern with other lines.
    <string> <string>
    
    lpn
    Replace lines not containing a pattern with other lines.
    <string> <string>
    
    lpf
    Replace lines containing a pattern with other lines once.
    <string> <string>
    
    lpfn
    Replace lines not containing a pattern with other lines once.
     <string> <string>

List of options in order:

-c
-cn
-cb
-cf
-cl
-ch
-cln
-cfn
-cbn
-cbf
-cbh
-cph
-cbph
-cbnh
-cbfn
-cpfh
-ml
-mp
-mpf
-mbl
-mbp
-mbpf
-dlpfn
-dlpn
-dln
-dlp
-dl
-dlpf
-dn
-dfn
-da
-daf
-db
-dbf
-dah
-dbh
-dafh
-dbfh
-d
-df
-r
-rf
-rl
-rln
-rlp
-rlpn
-rlpf
-rlpfn
-s
-sb
-sf
-st
-sh
-sbt
-sfh
-stf
-sbtf
-i
-ia
-ib
-if
-il
-iaf
-ial
-ian
-ibf
-ibp
-ibl
-iln
-ilp
-iafn
-ialn
-iblp
-ibln
-ibpn
-ibfn
-ibpf
-ilpn
-ilpf
-iblpf
-ibpfn
-ilpfn
-iblpfn
