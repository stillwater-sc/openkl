{% load kdev_filters %}
// {{ name }}.cpp
// Created: {% now "yyyy-MM-dd" %}
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)



#include <{% for n in namespaces %}{{n}}/{% endfor %}{{ name }}.hpp>



{% for n in namespaces %}namespace {{n}} { 
{% endfor %}



class {{ name }}
{


  public:



  private:

};



{% for n in namespaces %}}{% endfor %} // namespace {% for n in namespaces %}{{n}}{% if not forloop.last %}::{% endif %}{% endfor %}

