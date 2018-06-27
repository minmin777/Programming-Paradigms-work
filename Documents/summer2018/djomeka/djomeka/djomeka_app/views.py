from django.shortcuts import render
from djomeka_app.models import *
from djomeka_app.forms import SearchForm
from django.shortcuts import get_object_or_404
from django.contrib.postgres.search import SearchQuery, SearchRank, SearchVector

def index(request):
	return render(request, 'index.html')

def items(request):
	if request.method == 'POST':
		form = SearchForm(request.POST)
		query = request.POST.get('search', None)
		print(request.POST)
		if form.is_valid():
			sites = Items.objects.annotate(search=SearchVector('title', 'date')).filter(search=query)
			context = {'sites':sites, 'form':form}
			return render(request, 'items.html', context)
		else:
			print(form.errors)
	else:
		items = Items.objects.all()
		form = SearchForm()
		return render(request, 'items.html', {'items': items, 'form':form})

def item_view(request, title):
	item_view = Items.objects.filter(title=title)
	return render(request, 'item_view.html', {'items':item_view})
# Create your views here.
