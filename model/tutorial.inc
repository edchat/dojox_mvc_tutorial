<?php require("../../../resources/tutHead.inc"); ?>
<h3>Introduction to <code>dojo/Stateful</code></h3>
<p>
	<code>dojo/Stateful</code> provides the ability to get and set named properties, including using custom accessors in conjunction with the ability to monitor these properties for changes.
	<code>dojo/Stateful</code> is intended to be a base class that can be extended by other components that wish to support watchable properties.
	The interface of <code>dojo/Stateful</code> is very simple, there are three key methods:
</p>
<ul>
	<li><code>get(name)</code> - Retrieves the value of the given named property.</li>
	<li><code>set(name, value) - Sets the value of the given named property.</code></li>
	<li><code>watch(name, listener)</code> - Registers a callback for changes in the given property (first parameter can be omitted to listen for any changes).</li>
</ul>
<p>
	The constructor of dojo/Stateful lets you provide initial property values, like:
</p>
<pre class="brush: js;">
var obj = new Stateful({ // Stateful comes from dojo/Stateful module
	price: 9.99
});
</pre>
<p>
	And then you can get/set data:
</p>
<pre class="brush: js;">
obj.get("price"); // Returns 9.99
obj.set("price", 4.99); // price is now 4.99
obj.get("price"); // Returns 4.99
</pre>
<p>
	Also we can monitor that object for changes:
</p>
<pre class="brush: js;">
obj.watch("price", function(name, old, current){
	console.log("Price changed to " + current);
});

// price is now 3.99, and console output shows "Price changed to 3.99"
obj.set("price", 3.99);
</pre>
<h3>Creating custom model class with custom accessors</h3>
<p>
	<code>dojo/Stateful</code> supports the ability to define custom accessors (getters and setters) that allow control over how values of properties are set and retrieved, allowing model to encapsulate the internal data format.
</p>
<p>
	When a custom accessors is defined, a call to .get() or .set() will auto-magically use the custom accessor instead of accessing the property directly.
	A custom getter is defined in the format of <code>_xxxGetter</code> and a custom setter is defined in the format of <code>_xxxSetter</code> where the name of the property is <code>xxx</code>.
</p>
<p>
	A typical way to define custom accessors is creating a class based on <code>dojo/Stateful</code>, like below. In below code, <code>price</code> property is calculated based on <code>basePrice</code> property and <code>rate</code> property. Change in <code>basePrice</code> property and <code>rate</code> property will immediately be reflected to <code>price</code> property by <code>_changeAttrValue()</code>:
</p>
<pre class="brush: js;">
define("myModel", [
	"dojo/_base/declare",
	"dojo/Stateful"
], function(declare, Stateful){
	return declare(Stateful, {
		basePrice: 10,
		rate: 0.8,

		_priceGetter: function(){
			return this.basePrice * this.rate;
		},

		_basePriceSetter: function(value){
			this._changeAttrValue("price", value * this.rate);
			this.basePrice = value;
		},

		_rateSetter: function(value){
			this._changeAttrValue("price", this.basePrice * value);
			this.rate = value;
		}
	});
});

require([
	"myModel"
], function(myModel){
	var model = new myModel();
	model.watch("price", function(name, old, current){
		alert("New price: " + current);
	});
	alert(model.get("price")); // Alert box pops up showing "8"
	model.set("basePrice", 20); // Alert box pops up showing "16"
	model.set("rate", 0.5); // Alert box pops up showing "10"
});
</pre>
<h3><code>dojo/Stateful</code> resources</h3>
<p>
	Here are a few more resources about <code>dojo/Stateful</code>:
</p>
<ul>
	<li><a href="/reference-guide/1.8/dojo/Stateful.html"><code>dojo/Stateful</code> reference guide</a></li>
	<li><a href="/api/1.8/dojo/Stateful"><code>dojo/Stateful</code> API</a></li>
</ul>
<h3>Keep Going!</h3>
<p>
	Now that we've covered the basics of data model using <code>dojo/Stateful</code>, the next post in <code>dojox/mvc</code> series will focus on widget.
</p>
<?php include("../series.inc"); ?>
