from django import forms
from ckeditor.fields import RichTextField
from ckeditor.widgets import CKEditorWidget
import datetime

from django.db import models
from django.core.files.storage import FileSystemStorage
from djomeka_app.models import *

class SearchForm(forms.ModelForm):
	search = forms.CharField(label='search', max_length=100)
	class Meta:
		fields = ['title', 'date']
		model = Items
