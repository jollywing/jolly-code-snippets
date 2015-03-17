<?php // Time-stamp: <2011-11-27 Sun 16:21 classOrgile.php>

/* 

  ______________________
  C L A S S  O R G I L E

  classOrgile a very rough Org-Mode (http://orgmode.org/) file to HTML parser.
  This class is part of the Orgile publishing tool but can be used as a 
  standalone class. Please see http://toshine.org.

  Version 20110418

  Copyright (c) 2011 , 'Mash (Thomas Herbert) <letters@toshine.org>
  All rights reserved.

  This project was inspired by Dean Allen's "Textile" http://textile.thresholdstate.com/.

  NOTE: If you would like to help me develop this class properly rather then this
  amateur garden shed effort; please do contact me on the above address.

  _____________
  L I C E N S E

  This file is part of Orgile.
  Orgile: an Emacs Org-mode file parser and publishing tool.

  Orgile is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Orgile is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Orgile.  If not, see <http://www.gnu.org/licenses/>.

  _____________________
  D E S C R I P T I O N

  ClassOrgile converts "some" Org-mode markup into HTML. And yes you are right
  to question why since Org-mode has a mature HTML export already. http://orgmode.org

  require_once('classOrgile.php');
  $orgile = new orgile();
  return $orgile->orgileThis($content);

  The following org-mode markup is converted to HTML.
  Various glyphs are also replaced with their HTML entities.
  i.e. " (opening double quote) -> &#8220;

  * This is an example title.     -> <h1>This is an example title.</h1>
  ** This is an example title.    -> <h2>This is an example title.</h2>
  *** This is an example title.   -> <h3>This is an example title.</h3>
  **** This is an example title.  -> <h4>This is an example title.</h4>
  ***** This is an example title. -> <h5>This is an example title.</h5>

  This is an example of a paragraph. -> <p>This is an example of a paragraph</p>

  *example* -> <strong>example</strong>
  /example/ -> <em>example</em>
  +example+ -> <del>example</del>

  ----- -> <hr>

  #+begin_quote
  This is an example quote. -- Some Author. Some publication, 1975.
  #+end_quote

  -> <blockquote cite="Some Author. Some publication, 1975."><p>&#8220;This is an example quote.#8221;</p></blockquote><p class="citeRef">Some Author. Some publication, 1975.</p>

  #+begin_example
  This is an example.
  #+end_example

  -> <pre>This is an example.</pre>

  #+begin_src
  echo "Hello, World!";
  #+end_src

  -> <pre><code>echo "Hello, World!"</code></pre>

  [[http://www.link.com][example]] -> <a href="http://www.link.com" title="example">example</a>

  This is an example sentence with footnote.[1] -> This is an example sentence with footnote.<sup class="fnote"><a href="#fn1">1</a></sup>
  [1] This is an example footnote.              -> <p class="fnote"><sup id="fn1" class="fnote">1</sup>This is an example footnote.</p>',

*/

/*

TODO: (ADDED BY jollyWing)
- [done] enable <blockquote></blockquote> 2013-11-15 Fri
- [done] add `: xyz` 2013-11-15 Fri
- [done] add `=xy= ~xy~`, 2013-11-15 Fri
- [done] add `\\` to break line, 2013-11-16 Sat
- [done] paragraph in blockquote 2013-11-18 Mon
- [done] add support to [un]ordered list, 2013-11-21 Thu
- begin_src [language] 2013-11-15 Fri
*/

// ------------------------------[ CLASS ORGILE ]------------------------------
class orgile {

  // ----------[ ORGILE ]----------
  function orgileThis($text) {
    $text = $this->orgilise($text);
    $text = $this->codeReplace($text);
    $text = $this->footnotes($text);
    $text = $this->paragraph($text);
    return $text;
  }

  // added by JollyWing(jiqingwu@gmail.com), 2013-11-20 Wed
  function itemize($matches) {
    if(preg_match('/^\d+/', $matches[0]) == 1){
      $ordered = TRUE;
    }
    else {
      $ordered = FALSE;
    }

    $items = preg_split('+\r?\n+', $matches[0]);
    $out = '';
    foreach($items as $it) {
      if($it != ""){
        // $it = str_replace(array('- ','+ '), array('', ''), $it);
        $it = preg_replace(array('/^[\-\+]\s/', '/^\d+\.\s/'), array("", ''), $it);
        $out .= "<li>" . $it ."</li>\n";
      }
    }

    if($ordered){
      return "<ol>\n" . $out ."</ol>\n";
    }
    else {
      return "<ul>\n" . $out ."</ul>\n";
    }
  }
  // added by JollyWing(jiqingwu@gmail.com), 2013-11-20 Wed
  function itemizeList($text) {
    $patt = '/(^[\-\+]\s\S+.*?$\r?\n?)+/m';
    $result =  preg_replace_callback($patt, array($this, "itemize"), $text);

    $patt = '/(^\d+\.\s\S+.*?$\r?\n?)+/m';
    $result =  preg_replace_callback($patt, array($this, "itemize"), $result);
    return $result;
  }

  // ----------[ ORGALISE CONTENT ]----------
  // replace some general Org-mode markup with HTML.
  // NOTE: careful with changing order as links may be "glyphed"
  function orgilise($text) {
    $regex = array(
		   // headings
		   '/^\*{1}\s+?(.+)/m', // * example
		   '/^\*{2}\s+?(.+)/m', // ** example
		   '/^\*{3}\s+?(.+)/m', // *** example
		   '/^\*{4}\s+?(.+)/m', // **** example
		   '/^\*{5}\s+?(.+)/m', // ***** example

		   // typography
		   '/(?<!\S)\*(.+?)\*/m', // *example*
		   '/(?<!\S)\/(.+?)\//m', // /example/
		   '/(?<!\S)\+(.+?)\+/m', // +example+

           // added typography by JollyWing(jiqingwu@gmail.com), 2013-11-15
		   '/(?<!\S)=(.+?)=/m', // =example=
		   '/(?<!\S)~(.+?)~/m', // ~example~

		   // glyphs
		   // kudos: "Textile" http://textile.thresholdstate.com/.
		   '/(\w)\'(\w)/',                   // apostrophe's
		   '/(\s)\'(\d+\w?)\b(?!\')/',       // back in '88
		   '/(\S)\'(?=\s|[[:punct:]]|<|$)/', // single closing
		   '/\'/',                           // single opening
		   '/(\S)\"(?=\s|[[:punct:]]|<|$)/', // double closing
		   '/"/',                            // double opening
		   '/\b( )?\.{3}/',                  // ellipsis
		   '/(\s\w+)--(\w+\s)/',              // em dash
		   // '/\s-(?:\s|$)/',                  // en dash
		   '/(\d+)( ?)x( ?)(?=\d+)/',        // dimension sign
		   '/\b ?[([]TM[])]/i',              // trademark
		   '/\b ?[([]R[])]/i',               // registered
		   '/\b ?[([]C[])]/i',               // copyright

		   // horizontal rule
		   '/-{5,}/', // ----- (<hr/>)

           // <br/>, added by JollyWing (2013-11-16 Sat)
           '/([\s\S]*?)\\\\{2}\s{0,}$/mi', // xyz\\

		   // citations
		   '/#\+begin_quote\s([\s\S]*?)\s--\s(.*?)\s#\+end_quote/mi',

           // blockquote, added by JollyWing (2013-11-15 Fri)
		   '/#\+begin_quote\s([\s\S]*?)\s#\+end_quote/mi',

		   // pre
		   '/#\+begin_example\s([\s\S]*?)\s#\+end_example/mi',

		   // source
		   '/#\+begin_src\s([\s\S]*?)\s#\+end_src/mi',

		   // links
		   '/\[\[(.+?)\]\[(.+?)\]\]/m', // [[http://www.link.com][example]]

           // add ':', JollyWing(jiqingwu@gmail.com), 2013-11-15 Fri
           '/^\s{0,}:\s{0,}([\S\s]*?)$/m', // : xyz

           // add convertint '[+-] xyz' into unordered list
           // JollyWing, 2013-11-19 Tue
           // '/(^[\-\+]\s\S+.*?$\r?\n?)+/m',
		   );

    $replace = array(
		     // headings
		     "<h1>$1</h1>\n", // * example
		     "<h2>$1</h2>\n", // ** example
		     "<h3>$1</h3>\n", // *** example
		     "<h4>$1</h4>\n", // **** example
		     "<h5>$1</h5>\n", // ***** example

		     // typography
		     "<strong>$1</strong>", // *example*
		     "<em>$1</em>",         // /example/
		     "<del>$1</del>",       // +example+

             // added typography by JollyWing(jiqingwu@gmail.com), 2013-11-15
		     '<code>$1</code>', // =example=
		     '<code>$1</code>', // ~example~

		     // glyphs
		     "$1&#8217;$2",  // apostrophe's&#8220;
		     "$1&#8217;$2",  // back in '88
		     "$1&#8217;",    // single closing
		     "&#8216;",      // single opening
		     "$1&#8221;",    // double closing
		     "&#8220;",      // double opening
		     "$1&#8230;",    // ellipsis
		     "$1&#8212;$2",  // em dash
		     // "&#8211;",      // en dash
		     "$1$2&#215;$3", // dimension sign
		     "&#8482;",      // trademark
		     "&#174;",       // registered
		     "&#169;",       // copyright

		     // horizontal rule
		     "<hr>", // ----- (<hr>)

             // <br/>, added by JollyWing (2013-11-16 Sat)
             "$1<br/>",

		     // citations (because of the cite="$2" these fail W3M validation)
		     '<blockquote cite="$2"><p>$1</p></blockquote><p class="citeRef">$2</p>',

             // blockquote, added by JollyWing (2013-11-15 Fri)
		     '<blockquote>$1</blockquote>',

		     // pre
		     '<pre>$1</pre>',

		     // source
		     '<pre><code>$1</code></pre>',

		     // links
		     '<a href="$1" title="$2" target="_blank">$2</a>', // [[http://www.link.com][example]]

             // add ':', JollyWing(jiqingwu@gmail.com), 2013-11-15 Fri
		     '<pre><code>$1</code></pre>',
             
		     );

    $result = preg_replace($regex,$replace,$text);
    return $this->itemizeList($result);
  }

  // ----------[ CREATE FOOTNOTES ]----------
  // footnotes follow the pattern "example[n]" for id,  "[n] " for reference.
  function footnotes($text) {
    $regex = array(
		   '/(\S)\[([1-9]|[1-9][0-9])\]/',   // example[1]
		   '/\n\[([1-9]|[1-9][0-9])\](.*)/', // [1] example
		   );

    $replace = array(
		     '$1<sup class="fnote"><a href="#fn$2">$2</a></sup>',
		     '<p class="fnote"><sup id="fn$1" class="fnote">$1</sup>$2</p>',
		     );

    return preg_replace($regex,$replace,$text);
  }

  // ----------[ CODE REPLACE ]----------
  // use \"blah" in code and it will translated back into the "
  function codeReplace($code) {
    $dirty = array('\&#8216;','\&#8217;','\&#8220;','\&#8221;');
    $clean = array("'","'",'"','"');
    $code = str_replace($dirty, $clean, $code);
    return $code;
  }

  // ---------[ remove <p> and </p> between <pre></pre> ]----------
  // added by JollyWing(jiqingwu@gmail.com), 2013-11-18 Mon
  function cleanPre($text) {
    $patt = '/<pre>[\s\S]*?<\/pre>/';
    // NOTICE: anonymous function need php 5.3+
    $result =  preg_replace_callback($patt, function ($matches) { 
        return str_replace('<p>', '', str_replace('</p>', '', $matches[0]));
      }, $text);
    return $result;
  }

  // ----------[ PARAGRAPHS AND CLEANUP TAGS ]----------
  // create paragraphs and cleanup HTML tags.
  function paragraph($text) {
    // $paragraphs = explode("\n\n", $text);
    $paragraphs = preg_split("/\r{0,1}\n\r{0,1}\n/m", $text);
    /* $paragraphs = preg_split("/\n{2,}/m", $text); */
    $out = '';
    foreach($paragraphs as $paragraph) {
      $out .= "\n<p>".$paragraph."</p>\n";
    }

    /* echo "<pre>ADD &lt;P&gt;:$out</pre>"; */
    // cleanup paragraphs
    // due to the simplicity of the above there are many incorrect nested tags
    // i.e. <h1> elements inclosed in <p> tags.

    $regex = array(
		   '/<p>(<h[1-9]{1}>.+<\/h[1-9]{1}>)<\/p>/m',         // <p><h1>example</h1></p>
		   // '/<p>(<blockquote>[\s\S]+?)<\/p>/m',               // <p><blockquote>example</blockquote></p>
		   '/<p>\s{0,}<blockquote>([\s\S]+?)<\/blockquote>\s{0,}<\/p>/m',               // <p><blockquote>example</blockquote></p>
		   '/<p>(<blockquote cite=".+?">[\s\S]+?)<\/p>/m',    // <p><blockquote cite="example">example</blockquote></p>
		   '/<p>(<pre>[\s\S]*?<\/pre>)<\/p>/m',               // <p><pre>example</pre></p>
		   '/<p>(<p class="fnote">[\s\S]*?)\s+<\/p>/m',       // <p><p class="footnote">example</p></p>
		   // '/(<\/p>)\s+<\/p>/m',                              // <p></p>
		   '/<p>\s*<\/p>/m',                              // <p></p> fxied by JollyWing 2013-11-17
		   '/<p>(<hr>)<\/p>/',				      // <p><hr></p>
           '|<p>(<[ou]l>[\s\S]*?</[ou]l>)\s?</p>|mi', //added by JollyWing, 2013-11-19 Tue
		   );

    $replace = array(
		     "$1", // <hx>example</hx>
		     //"$1", // <blockquote>example</blockquote>
             "<blockquote><p>$1</p></blockquote>", // fixed by JollyWing (2013-11-15 Fri)
		     "$1", // <blockquote cite="example">example</blockquote>
		     "$1", // <pre>example</pre>
		     "$1", // <p class="footnote">example</p>
		     // "$1", //
             "",
		     "$1", // <hr>
             "$1", // <ul>..</ul> OR <ol>..</ol> added by JollyWing, 2013-11-19 Tue
		     );

    $out = preg_replace($regex,$replace,$out);
    /* echo "remove some &lt;p&gt;: $out"; */
    $out = $this->cleanPre($out);
    return $out;
  }

} // end: "class orgile {"
?>
