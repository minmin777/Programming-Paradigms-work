from django.contrib import admin
from djomeka_app.models import *

class ItemsAdmin(admin.ModelAdmin):
	pass
admin.site.register(Items, ItemsAdmin)
# Register your models here.
