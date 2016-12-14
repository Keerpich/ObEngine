-- Toolkit
Toolkit = {};
Toolkit.commands = {};
Toolkit.functions = {};

-- Globals
continue = true;
reload = true;
promptType = "Toolkit";

-- Commands Definition
Toolkit.commands.alias = {
	shortcuts = {"a", "alias"},
    args = {
        {name = "command", type = "string"},
        {name = "alias", type = "string"}
    }
};
Toolkit.commands.exit = {
	shortcuts = {"q", "quit", "exit"}
};
Toolkit.commands.help = {
    shortcuts = {"h", "help", "?"}
};
Toolkit.commands.package = {
    shortcuts = {"p", "pkg", "package"}, 
    args = {
        {name = "pkgname", type = "string"}, 
        {name = "output", type = "string"}, 
        {name = "compress", type = "boolean", optional = true}
    }
};
Toolkit.commands.reload = {
	shortcuts = {"r", "reload"}, 
};
Toolkit.commands.workspace = {
    shortcuts = {"w", "ws", "workspace"},
    args = {
        {name = "action", type = "string"},
        {name = "wsname", type = "string", optional = true}
    }
};

-- Permanent Aliases
require("Lib/Toolkit/Aliases");

-- Functions loading
for k, v in pairs(Toolkit.commands) do
    Toolkit.functions[k] = require("Lib/Toolkit/Functions/" .. k);
end

return Toolkit;