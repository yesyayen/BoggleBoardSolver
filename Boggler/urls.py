from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'Boggler.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^$', 'MainPage.views.index'),
    url(r'^index/', 'MainPage.views.index'),
    url(r'^admin/', include(admin.site.urls)),
)
