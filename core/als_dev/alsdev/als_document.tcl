##=================================================================================
# 		document.tcl
# 		Copyright (c) 1998 Applied Logic Systems, Inc.
#
# IDE Document windows.
#
# proenv indexes
#
# proenv(document_index) - Monotonically increasing index to create unique window names
#
# proenv(document_list)  - List of names of currently open documents
#
# proenv(document,$file) - Name of window which contains the file $file
#
#
# Document fields
# proenv($window,file) - Path to the file for this document. Empty string if untitled.
# proenv($window,dirty) - true iff document window is dirty.
#
##=================================================================================

set proenv(document_index) 0
set proenv(document_list) {}

proc create_document_window {title} {
	global array proenv
	global mod


	# Create a unique window name

	incr proenv(document_index)
	set w ".document$proenv(document_index)"
	
	# Create window

	toplevel $w
	wm title $w $title
	wm protocol $w WM_DELETE_WINDOW "document.close $w"

	# Setup menus

	menu $w.menubar -tearoff 0

	add_default_menus $w.menubar
	add_file_menu $w.menubar document $w
	add_edit_menu $w.menubar document $w
	add_prolog_menu $w.menubar document $w
	add_tools_menu $w.menubar document $w
	add_help_menu $w.menubar
		
	$w configure -menu $w.menubar		

	# Setup text and scrollbars
	
	text $w.text -yscrollcommand "$w.sb set" -setgrid true
	scrollbar $w.sb -command "$w.text yview"
	pack $w.sb -side right -fill both
	pack $w.text -fill both -expand 1 -side left
	$w.text configure -highlightthickness 0 \
		-background $proenv(.document,background) \
		-foreground $proenv(.document,foreground) \
		-selectbackground $proenv(.document,selectbackground) \
		-selectforeground $proenv(.document,selectforeground) \
		-font $proenv(.document,font) \
		-tabs $proenv(.document,tabs) 

	# accelerators
	bind_accelerators $w $mod document

	focus $w.text

	bind $w.text <KeyPress> "dirty_key $w %K"
	
	# Init document fields
	set proenv($w,dirty) false
	lappend proenv(document_list) $w
	
	return $w
}

proc dirty_key {w k} {
	global array proenv
	#.topals.text insert end $k
	if {$k!="Home" && $k!="End" && $k!="Prior" && $k!="Next" && $k!="Left" \
		&& $k!="Right" && $k!="Up" && $k!="Down"} {
		set proenv($w,dirty) true
	}
}

proc bind_accelerators {w mod type} {
	global tcl_platform
	
	if {"$tcl_platform(platform)" == "macintosh"} return;
	
	if {"$mod"=="Ctrl"} then { set MMD Control } else { set MMD $mod }

		# file menu:
	bind $w.text <$MMD-n> "$type.new"
	bind $w.text <$MMD-o> "$type.open"
	bind $w.text <$MMD-w> "$type.close $w"
	bind $w.text <$MMD-s> "$type.save $w"
	bind $w.text <$MMD-q> "exit_prolog"

		# edit menu:
#	 bind $w.text <$MMD-z> "$type.undo $w"

	 bind $w.text <$MMD-x> "$type.cut $w"
	 bind $w.text <$MMD-c> "$type.copy $w"
	 bind $w.text <$MMD-v> "$type.paste $w"
	 bind $w.text <$MMD-a> "$type.select_all $w"

		# prolog menu:
	bind $w.text <$MMD-k> "$type.consult $w"
}

proc dispose_document_window {w} {
	global array proenv
	if {[info exists proenv($w,file)] && [info exists proenv(document,$proenv($w,file))]} then {
		unset proenv(document,$proenv($w,file))
	}
	if {[info exists proenv($w,file)]} then {unset proenv($w,file)}
	if {[info exists proenv($w,dirty)]} then {unset proenv($w,dirty)}
	set i [lsearch -exact $proenv(document_list) $w]
	set proenv(document_list) [lreplace $proenv(document_list) $i $i]
	
	destroy $w
}


proc load_text {file text} {
	set s [open $file r]
	set data [read -nonewline $s]
	$text insert end $data
	close $s
}

proc store_text {text file} {
	set s [open $file w]
	set data [$text get 1.0 end]
	puts -nonewline $s $data
	close $s
}

proc load_document {file} {
	global array proenv
	if {[info exists proenv(document,$file)]} {
		raise $proenv(document,$file)
	} else {
		set file_name [lindex [file split $file] end]
		set w [create_document_window $file_name]		
		load_text $file $w.text
		set proenv($w,file) $file
		set proenv(document,$file) $w
	}
	return $proenv(document,$file)
}

# Document methods

proc document.new {} {
	create_document_window "Untitled"
}

proc document.open args {
	set file_list $args
	if {$file_list == ""} then {
		set file [tk_getOpenFile \
			-defaultextension pro \
			-title "Open File" \
			-filetypes {{"Prolog Files" {.pro .pl} TEXT}{"Tcl/Tk Files" {.tcl} TEXT}{{All Files} {*} TEXT} } ]
		if { "$file" != "" } then {
			set file_list [list $file]
		}
	}
	
	foreach file $file_list {
		load_document $file
	}
}

proc save_check {w} {
	global array proenv
	if {$proenv($w,dirty)} then {
		raise $w
		set title [wm title $w]
		set answer [tk_dialog .document_save_dialog "" \
			"Save changes to the document \"$title\" before closing?" \
			warning \
			2 "Don't Save" "Cancel" "Save"]
		if {$answer == 2} then {
			set result [document.save $w]
		} else {
			set result [expr $answer != 1]
		}
	} else {
		set result true
	}
	return $result
}


proc document.close {w} {
	if {[save_check $w]} then {
		dispose_document_window $w
		return true
	} else {
		return false
	}
}

proc document.close_all {} {
	global array proenv	
	foreach w $proenv(document_list) {
		if {![document.close $w]} then {return false}
	}
	return true
}

proc document.save {w} {
	global array proenv
	if {[info exists proenv($w,file)]} then {
		store_text $w.text $proenv($w,file)
		set proenv($w,dirty) false
		return true
	} else {
		return [document.save_as $w]
	}
}

proc document.save_as {w} {
	global array proenv
	set file [tk_getSaveFile -initialfile [wm title $w] \
		-defaultextension .pro ]
	if {$file != ""} then {
		if {[info exists proenv($w,file)]} then {
			unset proenv(document,$proenv($w,file))
		}
		set proenv($w,file) $file
		set proenv(document,$file) $w
		wm title $w [lindex [file split $file] end]
		return [document.save $w]
	} else {
		return false
	}
}

proc document.cut {w} {
 	if {![catch {set data [$w.text get sel.first sel.last]}]} {
	    clipboard clear -displayof $w
	    clipboard append -displayof $w $data
		$w.text delete sel.first sel.last
	}
}

proc document.copy {w} {
 	if {![catch {set data [$w.text get sel.first sel.last]}]} {
	    clipboard clear -displayof $w
	    clipboard append -displayof $w $data
	}
}

proc document.paste {w} {
	catch {$w.text delete sel.first sel.last}
	$w.text insert insert [selection get -displayof $w -selection CLIPBOARD]
	set proenv($w,dirty) true
}

proc document.clear {w} {
	global array proenv
	catch {$w.text delete sel.first sel.last}
	set proenv($w,dirty) true
}

proc document.select_all {w} {
	$w.text tag add sel 1.0 end
}

proc document.preferences {w} {

}

proc document.consult {w} {
	global array proenv

	set file $proenv($w,file)
	
	if {$file == ""} {
		if {![document.save $w]} {return}
	}
	
	if {$proenv($w,dirty)} {
		bell
		return
	}
	
	catch { prolog call alsdev do_reconsult -atom $file }
	insert_prompt  .topals.text "\n?-" 
}