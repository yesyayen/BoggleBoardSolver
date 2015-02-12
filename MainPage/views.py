from django.shortcuts import render
from django.shortcuts import render_to_response
from django.template import RequestContext
from django.core.context_processors import csrf
from django.views.decorators.csrf import csrf_exempt
import json, ast
from django.http import *
import commands
import cgi, cgitb


@csrf_exempt
def index(request):
    c = {}
    c.update(csrf(request))
    data = []

    if request.is_ajax():
        if request.method == "POST":
            if request.POST['operation'] == 'generateWords':
                print request.POST['boggleLetter']
                data = get_words(request.POST['boggleLetter'])

        return HttpResponse(json.dumps(data), content_type = "application/json")

    return render_to_response('index.html', c, RequestContext(request))


def get_words(boggleLetter):
    data = []
    data = commands.getstatusoutput('cd BoggleBoardAlgo;./boggle '+boggleLetter)[1].split("\n")
    return data