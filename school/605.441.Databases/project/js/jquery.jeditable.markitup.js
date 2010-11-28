/*
 * Universal markup editor for Jeditable
 *
 * Copyright (c) 2008 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 * 
 * Depends on markItUp! jQuery plugin by Jay Salvat:
 *   http://markitup.jaysalvat.com/
 *
 * Project home:
 *   http://www.appelsiini.net/projects/jeditable
 *
 * Revision: $Id: jquery.jeditable.markitup.js 350 2008-04-08 07:02:29Z tuupola $
 *
 */
 
$.editable.addInputType('markitup', {
    element : $.editable.types.textarea.element,
    plugin  : function(settings, original) {
        $('textarea', this).markItUp(settings.markitup);
    }
});
