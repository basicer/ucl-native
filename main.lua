print("Hello World")

local rx = replxx.new()
rx:install_window_change_handler()
rx:set_immediate_completion(true)
rx:set_double_tab_completion(true)

-- print("KEYS", type(replxx.keys))
-- for k,v in pairs(replxx.keys) do
--   print(k,v)
-- end

-- i(rx)
local x
print(replxx.keys.LEFT, replxx.keys.control('g'))
--rx:bind('a', 'move_cursor_to_begining_of_line')
--rx:bind(replxx.keys.UP, 'move_cursor_to_end_of_line')
--rx:bind(replxx.keys.F2, 'move_cursor_to_begining_of_line')

rx:set_completion_callback(function(ctx, len, ...)
	local x = ctx:sub(-len) or 'w'
	if len == 0 then return {} end

	return {
		Completion.new(x .. 'A'),
		Completion.new(x .. 'B', replxx.colors.RED),
	}
end)

-- rx:bind('a', function() print(22) end)

rx:set_hint_callback(function(text, len, ...)
	if #text > 14 then return {"faygo"} end
	if #text < 4 then return {} end
	return {
		text:sub(-len) .. " <- This is a hint: " .. table.concat({...}, "/"),
		"This is another hint",
		"Third hunt"
	}
end)

repeat
	x = rx:input("test> ")
	if x then
		rx:history_add(x)
		rx:print("Got " .. x)
	end
until x == nil