<?php require("../../../resources/tutHead.inc"); ?>
<h3>Introduction to <code>dojox/mvc/StatefulArray</code></h3>
<p>
	<code>dojo/Stateful</code> allows you to track change in property. Change in collection of data (array) happens somewhat in a different way from "change in property", rather in a way of adding/removing/updating array entries.
	JavaScript native array has several APIs supporing array change, but many of them end up with the <code>splice()</code> API.
	Dojo 1.8 introduced <code>dojox/mvc/StatefulArray</code> that extends JavaScript native array as well as <code>dojo/Stateful</code>, allowing you to track array splices.
</p>
<p>
	In addition to the APIs JavaScript native array and <code>dojo/Stateful</code> API have, <code>dojox/mvc/StatefulArray</code> has <code>watchElements()</code> API, which takes a callback function called when change in array elements happens, like:
</p>
<pre class="brush: js;">
a.watchElements(function(idx, removals, adds){
	// The callback function notifying change in array elements
});
</pre>
<p>
	The arguments in the callback function are the following:
	<ol>
		<li><code>idx</code> - The array index where the change happened</li>
		<li><code>removals</code> - The array elements that are removed
		<li><code>adds</code> - The array elements that are added
	</ol>
	When an array API that changes the entire array elements (like <code>reverse()</code>) is called, the callback is called with no argument.
</p>
<p>
	Below code shows how calling array API of <code>dojox/mvc/StatefulArray</code> ends up with the callback:
</p>
<pre class="brush: js;">
require(["dojox/mvc/StatefulArray"], function(StatefulArray){
	var a = new StatefulArray([0, 1, 2]); // Create a new StatefulArray
	a.watchElements(function(idx, removals, adds){
		if(!isNaN(idx)){
			alert("At " + idx + ", removed " + (removals.length > 0 ? removals : "nothing") + " and added " + (adds.length > 0 ? adds : "nothing"));
		}else{
			alert("The whole array has been updated");
		}
	});

	a.push(3); // Alert box pops up saying "At 3, removed nothing and added 3"
	a.reverse(); // Alert box pops up saying "The whole array has been updated"
	a.shift(); // Alert box pops up saying "At 0, removed 3 and added nothing"
});
</pre>
<a class="demoBtn demo" href="demo/StatefulArray.html">View Demo</a>
<h3>Creating a collection of <code>dojo/Stateful</code>-based model</h3>
<p>
	The most typical way to create data model from collection of data in <code>dojox/mvc</code> is creating <code>dojox/mvc/StatefulArray</code> containing <code>dojo/Stateful</code> as its entries.
	<code>dojox/mvc</code> provides <code>dojox/mvc/getStateful</code>, that helps create data model by taking a parameter list specifying what type of data is converted (to data model) how.
</p>
<p>
	For example, below code creates <code>dojox/mvc/StatefulArray</code> for the given array, and the array elements become <code>dojo/Stateful</code> if they are objects (intact otherwise):
</p>
<pre class="brush: js;">
require([
	"dojo/_base/array",
	"dojo/_base/lang",
	"dojo/Stateful",
	"dojox/mvc/getStateful",
	"dojox/mvc/StatefulArray"
], function(array, lang, Stateful, getStateful, StatefulArray){
	var a = getStateful([
		{title: "Update my PC"},
		"Walk my dog"
	], {
		getType: function(v){
			return lang.isArray(v) ? "array" : v != null && {}.toString.call(v) == "[object Object]" ? "object" : "value";
		},
		getStatefulArray: function(a){
			return new StatefulArray(array.map(a, function(item){ return getStateful(item, this); }, this));
		},
		getStatefulObject: function(o){
			return new Stateful(o);
		},
		getStatefulValue: function(v){
			return v;
		}
	});

	a.watchElements(function(idx, removals, adds){
		if(!isNaN(idx)){
			alert("At " + idx + ", removed " + (removals.length > 0 ? removals : "nothing") + " and added " + (adds.length > 0 ? adds : "nothing"));
		}else{
			alert("The whole array has been updated");
		}
	}); // Can set element watch callback as the array is dojox/mvc/StatefulArray

	a[0].watch(function(name, old, current){
		alert("Property " + name + " has been changed to: " + current);
	}); // Can set property watch callback as the 1st element is dojo/Stateful

	alert(a[1]); // Shows "Walk my dog"
	a[0].set("title", "Update my tablet"); // Alert box pops up saying "Property title has been changed to: Update my tablet"
	a.unshift("Wash my car"); // Alert box pops up saying "At 0, removed nothing and added Wash my car"
});
</pre>
<a class="demoBtn demo" href="demo/getStateful.html">View Demo</a>
<h3>Collection of <code>dojo/Stateful</code>-based model with custom accessors</h3>
<p>
	Sometimes <code>dojo/Stateful</code> as entries of <code>dojox/mvc/StatefulArray</code> need custom accessors.
	It can be achived applying custom accessors to initial entries as well as newly added entries.
</p>
<p>
	Below example sets a custom accessor (<code>_markedSetter()</code>), which updates how many entries have <code>marked = true</code>, to initial elements as well as newly added elements by tracking additions by <code>watchElements()</code>.
	The array is tracked of removal of elements, too, to update the number of entries with <code>marked = true</code>:
</p>
<pre class="brush: js;">
require([
	"dojo/_base/array",
	"dojo/_base/declare",
	"dojo/_base/lang",
	"dojo/Stateful",
	"dojox/mvc/getStateful",
	"dojox/mvc/StatefulArray"
], function(array, declare, lang, Stateful, getStateful, StatefulArray){
	var sa = getStateful({title: "Wash my car", marked: true}, {
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

	alert(sa.marked); // Shows "1"

	sa.push({title: "Misc", marked: true});
	alert(sa.marked); // Shows "2"

	sa.pop();
	alert(sa.marked); // Shows "1"
});
</pre>
<a class="demoBtn demo" href="demo/accessor.html">View Demo</a>
<h3><code>dojox/mvc/StatefulArray</code> and <code>dojox/mvc/getStateful</code> resources</h3>
<p>
	Here are a few more resources about <code>dojox/mvc/StatefulArray</code> and <code>dojox/mvc/getStateful</code>:
</p>
<ul>
	<li><a href="/reference-guide/1.8/dojox/mvc/StatefulArray.html"><code>dojox/mvc/StatefulArray</code> reference guide</a></li>
	<li><a href="/api/1.8/dojox/mvc/StatefulArray"><code>dojox/mvc/StatefulArray</code> API</a></li>
	<li><a href="/reference-guide/1.8/dojox/mvc/getStateful.html"><code>dojox/mvc/getStateful</code> reference guide</a></li>
	<li><a href="/api/1.8/dojox/mvc/getStateful"><code>dojox/mvc/getStateful</code> API</a></li>
</ul>
<h3>Keep Going!</h3>
<p>
	Now that we've covered the basics of collection using <code>dojox/mvc/StatefulArray</code>, the next post in <code>dojox/mvc</code> series will focus on (list of) widgets working with collection.
</p>
<?php include("../series.inc"); ?>
