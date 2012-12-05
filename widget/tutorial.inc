<?php require("../../../resources/tutHead.inc"); ?>
<h3>Background</h3>
<p>
	Starting Dojo 1.6, all Dijit widgets are based on <code>dojo/Stateful</code>.
	Widget attributes, such as values in form widgets, are defined as <code>dojo/Stateful</code> properties.
	It means that you can use standardized <code>dojo/Stateful</code> API to change widget attribtues, and widgets will react to such change in attributes.
</p>
<p>
	Dojo 1.8 introduced <code>dojox/mvc/sync</code> API which allows to keep properties in two <code>dojo/Stateful</code> in sync.
	Dojo 1.8 also introduced <code>dojox/mvc/at</code> API, which wraps <code>dojox/mvc/sync</code> API, by being used as initial attribute value of widget to specify the attribute should be in sync with what <code>dojo/Stateful</code> property.
	It allows to make out-of-the-box Dijit widgets react to change in model property, by keeping property in data model and widget attribute in sync.
</p>
<h3>Using <code>dojox/mvc/at</code> API in <code>data-dojo-props</code></h3>
<p>
	The most typical way to bind widget attribute with data model property is using <code>dojox/mvc/at</code> API in <code>data-dojo-props</code> HTML attribute, which specifies initial attribute (property) values of widget:
</p>
<pre class="brush: js; html-script: true">
&lt;html&gt;
	&lt;head&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/resources/dojo.css" /&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dijit/themes/claro/claro.css" /&gt;
		&lt;script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/dojo.js"
		 data-dojo-config="parseOnLoad: 1, async: 1, deps: ['dojo/parser']"&gt;&lt;/script&gt;
	&lt;/head&gt;
	&lt;body&gt;
		&lt;script type="dojo/require"&gt;at: "dojox/mvc/at"&lt;/script&gt;
		&lt;span data-dojo-id="model"
		 data-dojo-type="dojo/Stateful"
		 data-dojo-props="value: 'Foo'"&gt;
		&lt;input type="text"
		 data-dojo-type="dijit/form/TextBox"
		 data-dojo-props="value: at(model, 'value')"&gt;
		&lt;span data-dojo-type="dojox/mvc/Output"
		 data-dojo-props="value: at(model, 'value')"&gt;&lt;/span&gt;
	&lt;/body&gt;
&lt;/html&gt;
</pre>
<a class="demoBtn demo" href="demo/declarative.html">View Demo</a>
<p>
	In above example, a text is shown next to the text box showing the same value.
	<code>&lt;input&gt;</code> as well as the following <code>&lt;span&gt;</code> are bound to the same <code>value</code> property in <code>model</code>.
	<code>model</code> is defined in the 1st <code>&lt;span&gt;</code>, setting "foo" to the initial value of <code>value</code> property.
	<code>&lt;script type="dojo/require"&gt;</code> block allows you to refer to <code>dojox/mvc/at</code> AMD module as <code>at</code> in <code>data-dojo-props</code> (new to 1.8).
</p>
<p>
	<code>dojox/mvc/at</code> API as well as <code>dojox/mvc/sync</code> API works with any widget attribute.
	Below example shows how tool bar item can react to model properties:
</p>
<pre class="brush: js; html-script: true">
&lt;html&gt;
	&lt;head&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/resources/dojo.css" /&gt;
		&lt;link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dijit/themes/claro/claro.css" /&gt;
		&lt;script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/dojo/1.8.1/dojo/dojo.js"
		 data-dojo-config="parseOnLoad: 1, async: 1, deps: ['dojo/parser']"&gt;&lt;/script&gt;
	&lt;/head&gt;
	&lt;body class="claro"&gt;
		&lt;script type="dojo/require"&gt;at: "dojox/mvc/at"&lt;/script&gt;
		&lt;span data-dojo-id="model"
		 data-dojo-type="dojo/Stateful"
		 data-dojo-props="menuLabel: 'Click me!', menuDisabled: false"&gt;
		&lt;div data-dojo-type="dijit/MenuBar"&gt;
			&lt;div data-dojo-type="dijit/MenuBarItem"
			 data-dojo-props="label: at(model, 'menuLabel'), disabled: at(model, 'menuDisabled')"&gt;
			&lt;/div&gt;
		&lt;/div&gt;
		&lt;div&gt;
			&lt;input id="check" type="checkbox"
			 data-dojo-type="dijit/form/CheckBox"
			 data-dojo-props="checked: at(model, 'menuDisabled')"&gt;
			&lt;label for="check"&gt;Disable the toolbar item&lt;/label&gt;
		&lt;/div&gt;
		&lt;div&gt;
			&lt;label for="text"&gt;Menu label&lt;/label&gt;
			&lt;input id="text" data-dojo-type="dijit/form/TextBox"
			 data-dojo-props="value: at(model, 'menuLabel')"&gt;
		&lt;/div&gt;
	&lt;/body&gt;
&lt;/html&gt;
</pre>
<a class="demoBtn demo" href="demo/Toolbar.html">View Demo</a>
<h3><code>dojox/mvc/at</code>, <code>dojox/mvc/sync</code> and widget resources</h3>
<p>
	Here are a few more resources about <code>dojox/mvc/at</code>, <code>dojox/mvc/sync</code> and widget:
</p>
<ul>
	<li><a href="/reference-guide/1.8/dojox/mvc/at.html"><code>dojox/mvc/at</code> reference guide</a></li>
	<li><a href="/api/1.8/dojox/mvc/at"><code>dojox/mvc/at</code> API</a></li>
	<li><a href="/reference-guide/1.8/dojox/mvc/sync.html"><code>dojox/mvc/sync</code> reference guide</a></li>
	<li><a href="/api/1.8/dojox/mvc/sync"><code>dojox/mvc/sync</code> API</a></li>
	<li><a href="https://dojotoolkit.org/reference-guide/1.8/dijit/_WidgetBase.html#attributes">Widget attributes</a></li>
	<li><a href="/reference-guide/1.8/dojo/parser.html#parser-parameters"><code>data-dojo-props</code></a></li>
	<li><a href="/reference-guide/1.8/dojo/parser.html#declarative-require"><code>&lt;script type="dojo/require"&gt;</code></a></li>
</ul>
<h3>Keep Going!</h3>
<p>
	Now that we've covered the basics of using widget with <code>dojo/Stateful</code>-based model, the next post in <code>dojox/mvc</code> series will focus on collection of data model.
</p>
<?php include("../series.inc"); ?>
