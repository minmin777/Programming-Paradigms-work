from django.db import models
from ckeditor.fields import RichTextField
from django.template.defaultfilters import slugify
#from djrichtextfield.models import RichTextField
import datetime


class Items(models.Model):
	title = models.CharField(max_length=30)
	slug = models.SlugField(max_length=30, blank=True, null=True)
	description = RichTextField()
	files = models.FileField(upload_to='static/')
	url = models.URLField(max_length=200, blank=True, null=True)
	date = models.DateField(default=datetime.date.today)
	attributes = models.TextField(blank=True, null=True)
	def save(self, *args, **kwargs):
		if not self.id:
			self.slug = slugify(self.title)
		super(Items, self).save(*args, **kwargs)

	def __str__(self):
		return self.title

	
# Create your models here.
