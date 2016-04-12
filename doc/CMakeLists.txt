# Copyright Barrett Adair 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)


# 100% HACKS - JUST FOR ME

add_custom_target(doc COMMENT "Building the HTML documentation.")

add_custom_command(TARGET doc
                   PRE_BUILD
                   COMMAND b2
                   ${CMAKE_CURRENT_LIST_DIR})
				   
add_custom_command(TARGET doc
			   POST_BUILD
			   COMMAND powershell
			   ARGS -Command "Get-ChildItem .\\html\\callable_traits *.html | Foreach-Object { $$file = $$_.FullName ; (Get-Content $$file) -replace '../../../doc/src/', '../../src/' | Set-Content $$file }"
			   )

add_custom_command(TARGET doc
			   POST_BUILD
			   COMMAND powershell
			   ARGS -Command "Get-ChildItem .\\html *.html | Foreach-Object { $$file = $$_.FullName ; (Get-Content $$file) -replace '../../doc/src/', '../src/' | Set-Content $$file }"
			   )

add_custom_command(TARGET doc
                   POST_BUILD
                   COMMAND robocopy
				   ARGS ..\\..\\doc\\src\\css html
                   )
				   
add_custom_command(TARGET doc
                   POST_BUILD
                   COMMAND robocopy
				   ARGS /MIR html ..\\..\\doc\\html
                   )




