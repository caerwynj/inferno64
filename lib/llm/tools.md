# read
Read a text file. Returns lines [offset .. offset+limit-1] (1-indexed).
Defaults: offset=1, limit=2000.

```json
{"type":"object",
 "properties":{"path":{"type":"string","description":"File path (relative or absolute)"},
               "offset":{"type":"integer","description":"1-indexed first line"},
               "limit":{"type":"integer","description":"Maximum number of lines"}},
 "required":["path"]}
```

# write
Write content to a file, overwriting if it exists. Creates parent directories.

```json
{"type":"object",
 "properties":{"path":{"type":"string"},
               "content":{"type":"string"}},
 "required":["path","content"]}
```

# edit
Replace exact text in a file. oldText must match exactly (including whitespace) and must be unique in the file. If oldText appears more than once, the edit is refused.

```json
{"type":"object",
 "properties":{"path":{"type":"string"},
               "oldText":{"type":"string"},
               "newText":{"type":"string"}},
 "required":["path","oldText","newText"]}
```

# multi_edit
Apply several edits to one file atomically. Each edit has the same uniqueness requirement as edit. Edits apply in order against the running buffer.

```json
{"type":"object",
 "properties":{"path":{"type":"string"},
               "edits":{"type":"array",
                        "items":{"type":"object",
                                 "properties":{"oldText":{"type":"string"},
                                               "newText":{"type":"string"}},
                                 "required":["oldText","newText"]}}},
 "required":["path","edits"]}
```

# shell
Execute an inferno shell command. Returns combined stdout+stderr. Optional timeout (seconds; 0 or omitted means no timeout).

```json
{"type":"object",
 "properties":{"command":{"type":"string"},
               "timeout":{"type":"integer","description":"seconds; 0 = no timeout"}},
 "required":["command"]}
```

# ls
List a directory or stat a single file. Output: "<kind> <length> <name>" per line; kind is 'd' for directories and '-' for regular files.

```json
{"type":"object",
 "properties":{"path":{"type":"string"}},
 "required":["path"]}
```

# glob
Recursively find files matching a basename pattern under dir. Pattern supports a single '*' as prefix or suffix. Capped at 500 results.

```json
{"type":"object",
 "properties":{"dir":{"type":"string"},
               "pattern":{"type":"string"}},
 "required":["dir","pattern"]}
```

# grep
Regex search via inferno grep. Output is file:line:match.

```json
{"type":"object",
 "properties":{"pattern":{"type":"string"},
               "path":{"type":"string"}},
 "required":["pattern","path"]}
```
