/*
function Escape(text) {
   return text.replace(/&/g,'&amp;').
     replace(/</g,'&lt;').
     replace(/"/g,'&quot;').
     replace(/'/g,'&#039;');
}
*/

function escapeHTML(s) {
   var MAP = {
     '&': '&amp;',
     '<': '&lt;',
     '>': '&gt;',
     '"': '&#34;',
     "'": '&#39;'
   };
   var repl = function(c) { return MAP[c]; };
   return s.replace(/[&<>'"]/g, repl);
}

exports.escapeHTML = escapeHTML;
