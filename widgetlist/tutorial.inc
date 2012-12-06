<?php require("../../../resources/tutHead.inc"); ?>
<h3>Introduction to <code>dojox/mvc/WidgetList</code></h3>
<p>
	<code>dojox/mvc/WidgetList</code> is a widget that creates child widgets repeatedly based on ghe given collection (<code>children</code> attribute).
	The simplest usage of <code>dojox/mvc/WidgetList</code> is like below, which creates <code>dijit/form/TextBox</code> repeatedly based on <code>array</code>:
</p>
<pre class="brush: js; html-script: true">
&lt;div data-dojo-type="dojox/mvc/WidgetList"
 data-dojo-props="children: array"
 data-mvc-child-type="dijit/form/TextBox"
 data-mvc-child-props="value: at(this.target, 'First')"&gt;&lt;/div&gt;
</pre>
<a class="demoBtn demo" href="demo/simple.html">View Demo</a>
<p>
	In above example, <code>this.target</code> in <code>data-mvc-child-props</code> points to the array entry.
</p>
<p>
	Often you'd want to create HTML fragments repeatedly. You can do it too with <code>dojox/mvc/WidgetList</code>:
</p>
<pre class="brush: js; html-script: true">
&lt;div data-dojo-type="dojox/mvc/WidgetList"
 data-dojo-mixins="dojox/mvc/_InlineTemplateMixin"
 data-dojo-props="children: array"&gt;
	&lt;script type="dojox/mvc/InlineTemplate"&gt;
		&lt;div&gt;
			&lt;span data-dojo-type="dojox/mvc/Output"
			 data-dojo-props="value: at(this.target, 'Serial')"&gt;&lt;/span&gt;: 
			&lt;span data-dojo-type="dijit/form/TextBox"
			 data-dojo-props="value: at(this.target, 'First')"&gt;&lt;/span&gt;
		&lt;/div&gt;
	&lt;/script&gt;
&lt;/div&gt;
</pre>
<a class="demoBtn demo" href="demo/template.html">View Demo</a>
<p>
	<code>dojox/mvc/_InlineTemplateMixin</code> in above example sets the HTML inside <code>&lt;script type="dojox/mvc/InlineTemplate"&gt;</code> to the template string (<code>templateString</code>).
	In the template, <code>this.target</code> in <code>data-dojo-props</code> points to the array entry.
</p>
<p class="proTip">
	You can directly set <code>templateString</code> to <code>dojox/mvc/WidgetList</code>'s property (via <code>data-dojo-props</code>, etc.), too, instead of using <code>dojox/mvc/_InlineTemplateMixin</code> and <code>&lt;script type="dojox/mvc/InlineTemplate"&gt;</code>.
</p>
<h3>Reflecting change in collection</h3>
<p>
	By using <code>dojox/mvc/StatefulArray</code> as the <code>children</code> attribute, <code>dojox/mvc/WidgetList</code> automatically adds/removes child widgets as entries in <code>dojox/mvc/StatefulArray</code> are added/removed.
	Below code has two action button handlers (<code>addEntry()</code> and <code>removeEntry()</code>), and both of them adds or removes array entry, which end up with the UI for added or removed:
</p>
<pre class="brush: js; html-script: true">
&lt;html&gt;
	&lt;head&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/resources/dojo.css" /&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dijit/themes/claro/claro.css" /&gt;
		&lt;script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/dojo.js"
		 data-dojo-config="parseOnLoad: 0, async: 1"&gt;&lt;/script&gt;
		&lt;script type="text/javascript"&gt;
			require([
				"dojo/parser",
				"dojo/Stateful",
				"dojox/mvc/StatefulArray",
				"dijit/form/TextBox",
				"dojox/mvc/Output",
				"dojo/domReady!"
			], function(parser, Stateful, StatefulArray){
				var serial = 100003;
				newEntry = new Stateful({value: ""});
				array = new StatefulArray([
					{Serial: 100000, First: "Anne"},
					{Serial: 100001, First: "Ben"},
					{Serial: 100002, First: "Irene"}
				]);
				addEntry = function(){
					array.push(new Stateful({Serial: serial++, First: newEntry.value}));
				};
				removeEntry = function(serial){
					for(var i = array.length - 1; i >= 0; --i){
						if(array[i].Serial == serial){
							array.splice(i, 1);
							return;
						}
					}
				};
				parser.parse();
			});
		&lt;/script&gt;
	&lt;/head&gt;
	&lt;body class="claro"&gt;
		&lt;script type="dojo/require"&gt;at: "dojox/mvc/at"&lt;/script&gt;
		&lt;div data-dojo-type="dojox/mvc/WidgetList"
		 data-dojo-mixins="dojox/mvc/_InlineTemplateMixin"
		 data-dojo-props="children: array"&gt;
			&lt;script type="dojox/mvc/InlineTemplate"&gt;
				&lt;div&gt;
					&lt;span data-dojo-type="dojox/mvc/Output"
					 data-dojo-props="value: at(this.target, 'Serial')"&gt;&lt;/span&gt;: 
					&lt;span data-dojo-type="dijit/form/TextBox"
					 data-dojo-props="value: at(this.target, 'First')"&gt;&lt;/span&gt;
					&lt;input type="button"
					 data-dojo-type="dijit/form/Button"
					 data-dojo-props="label: 'Remove', Serial: at(this.target, 'Serial'), onClick: function(){ removeEntry(this.Serial); }"&gt;
				&lt;/div&gt;
			&lt;/script&gt;
		&lt;/div&gt;
		&lt;div&gt;
			&lt;label for="add"&gt;Add an entry:&lt;/label&gt;
			&lt;input id="add"
			 data-dojo-type="dijit/form/TextBox"
			 data-dojo-props="value: at(newEntry, 'value')"&gt;
			&lt;input type="button"
			 data-dojo-type="dijit/form/Button"
			 data-dojo-props="onClick: addEntry, label: 'Add'"&gt;
		&lt;/div&gt;
	&lt;/body&gt;
&lt;/html&gt;
</pre>
<a class="demoBtn demo" href="demo/splice.html">View Demo</a>
<h3>Working with collection of <code>dojo/Stateful</code>-based model</h3>
<p>
	By putting together collection of <code>dojo/Stateful</code>-based model discussed in previous post and <code>dojox/mvc/WidgetList</code>, you can create repeating UI from collection of custom model.
	For example, below code keeps number of checked items updated, by having custom model keep track of it:
</p>
<pre class="brush: js; html-script: true">
&lt;html&gt;
	&lt;head&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/resources/dojo.css" /&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dijit/themes/claro/claro.css" /&gt;
		&lt;script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/dojo.js"
		 data-dojo-config="parseOnLoad: 0, async: 1"&gt;&lt;/script&gt;
		&lt;script type="text/javascript"&gt;
			require([
				"dojo/_base/array",
				"dojo/_base/lang",
				"dojo/parser",
				"dojo/Stateful",
				"dojox/mvc/getStateful",
				"dojox/mvc/StatefulArray",
				"dijit/form/Button",
				"dijit/form/CheckBox",
				"dijit/form/TextBox",
				"dojox/mvc/Output"
			], function(array, lang, parser, Stateful, getStateful, StatefulArray){
				newEntry = new Stateful({value: ""});

				var uniqueId = 100003;

				sa = getStateful([
					{uniqueId: 100000, title: "Wash my car"},
					{uniqueId: 100001, title: "Walk my dog", marked: true}
				], {
					getType: function(v){
						return lang.isArray(v) ? "array" : "value";
					},

					getStatefulArray: function(a){
						var sa = new StatefulArray([]);
						sa.watchElements(function(idx, removals, adds){
							array.forEach(removals, function(item){
								sa.set("marked", sa.marked - !!item.marked);
							});
							array.forEach(adds, function(item){
								item._markedSetter = function(value){
									if(this.parent && (this.marked ^ value)){ // When the value is changed...
										this.parent.set("marked", (this.parent.marked || 0) + (value ? 1 : -1)); // Update total number of marked entries reflecting the new state
									}
									this.marked = value;
								};
								sa.set("marked", (sa.marked || 0) + (!!item.marked - 0)); // Update total number of marked entries reflecting the initial state
								item.parent = sa;
								item.uniqueId = item.uniqueId || uniqueId++;
							});
						});
						sa.push.apply(sa, array.map(a, function(item){
							return new Stateful(item);
						}));
						return sa;
					},

					getStatefulValue: function(v){
						return getStateful([v], this);
					}
				});


				addEntry = function(){
					sa.push(new Stateful({title: newEntry.value}));
				};
				removeEntry = function(uniqueId){
					for(var i = sa.length - 1; i &gt;= 0; --i){
						if(sa[i].uniqueId == uniqueId){
							sa.splice(i, 1);
							return;
						}
					}
				};

				parser.parse();
			});
		&lt;/script&gt;
	&lt;/head&gt;
	&lt;body class="claro"&gt;
		&lt;script type="dojo/require"&gt;at: "dojox/mvc/at"&lt;/script&gt;
		&lt;div&gt;
			Marked entries:
			&lt;span data-dojo-type="dojox/mvc/Output"
			 data-dojo-props="value: at(sa, 'marked')"&gt;&lt;/span&gt;
		&lt;/div&gt;
		&lt;div data-dojo-type="dojox/mvc/WidgetList"
		 data-dojo-mixins="dojox/mvc/_InlineTemplateMixin"
		 data-dojo-props="children: sa"&gt;
			&lt;script type="dojox/mvc/InlineTemplate"&gt;
				&lt;div&gt;
					&lt;span data-dojo-type="dijit/form/CheckBox"
					 data-dojo-props="checked: at(this.target, 'marked')"&gt;&lt;/span&gt;
					&lt;span data-dojo-type="dijit/form/TextBox"
					 data-dojo-props="value: at(this.target, 'title')"&gt;&lt;/span&gt;
					&lt;input type="button"
					 data-dojo-type="dijit/form/Button"
					 data-dojo-props="label: 'Remove', uniqueId: at(this.target, 'uniqueId'), onClick: function(){ removeEntry(this.uniqueId); }"&gt;
				&lt;/div&gt;
			&lt;/script&gt;
		&lt;/div&gt;
		&lt;div&gt;
			&lt;label for="add"&gt;Add an entry:&lt;/label&gt;
			&lt;input id="add"
			 data-dojo-type="dijit/form/TextBox"
			 data-dojo-props="value: at(newEntry, 'value')"&gt;
			&lt;input type="button"
			 data-dojo-type="dijit/form/Button"
			 data-dojo-props="onClick: addEntry, label: 'Add'"&gt;
		&lt;/div&gt;
	&lt;/body&gt;
&lt;/html&gt;
</pre>
<a class="demoBtn demo" href="demo/modelcollection.html">View Demo</a>
<h3><code>dojox/mvc/WidgetList</code> resources</h3>
<p>
	Here are a few more resources about <code>dojox/mvc/WidgetList</code>:
</p>
<ul>
	<li><a href="/reference-guide/1.8/dojox/mvc/WidgetList.html"><code>dojox/mvc/WidgetList</code> reference guide</a></li>
	<li><a href="/api/1.8/dojox/mvc/WidgetList"><code>dojox/mvc/WidgetList</code> API</a></li>
</ul>
<?php include("../series.inc"); ?>
