Wobble
======

An open source code generation and bootstrapping framework

Overview
--------

Wobble uses a plugin system for reading and writing code.
An `Input` is used to parse or other import a project structure
(classes, functions, signals). Once imported, one or more 
generators, called `Outputs` are used to convert the definition
into actual code. 

Uses
----

Wobble is meant to be used for generating object-oriented code. 
It supports classes with members, methods, and signals. 

The goal is to be able to define a class and user interface structure,
and Wobble would create projects for a desktop application, a web 
application, and a mobile application. All these applications would use
native widgets, but would look and function very similar. 


Modules (planned)
-----------------

* Database-backed persistent classes
* Common user interfaces
* OpenGL

Current State
-------------

So far, there is only one input plugin (YAML) and one output (C++/Qt). 
Other outputs are planned, like Python/Django and Java. 
