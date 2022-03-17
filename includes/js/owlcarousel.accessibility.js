// Initialise OwlCarousel accessibility plugin

var owlAccess = {};

// Wrap inside code for runtime initialisation
(function($){

  // Utility functions

  owlAccess.util = {
    generateUUID: function() {
      var d = new Date().getTime();
      var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
          var r = (d + Math.random()*16)%16 | 0;
          d = Math.floor(d/16);
          return (c=='x' ? r : (r&0x3|0x8)).toString(16);
      });
      return uuid;
    },
    uniqueID: function(scope) {
      return scope + "-" + owlAccess.util.generateUUID();
    },
    debug: function(msg) {
      // console.log(msg + " " + Date.now());
    }
  };

  // Accessibility functions

  owlAccess.a11y = {
    base: {
      setup: function(elem) {
        elem.attr('tabindex', '0')
            .attr('data-owl-carousel-focusable', '1')
            .attr('aria-live', 'off')
            .attr('aria-atomic', 'true')
            .attr('aria-relevant', 'additions')
            .attr('aria-busy', 'true');
        elem.bind('keyup', owlAccess.events.eventResponse.documentKeyUp);
        elem.attr('data-owl-access-keyup', '1');
      },
      busy: function(elem, isBusy) {
        $(elem).attr('aria-busy', isBusy.toString());
      }
    },
    controls: {
      setup: function(elem) {
        var controlsID = owlAccess.util.uniqueID('owl-controls');
        elem.find('.owl-controls')
            .attr('id', controlsID)
            .attr('aria-hidden', 'true');
        elem.attr('aria-controls', controlsID);
      }
    },
    description: {
      hasDescription: function(elem){
        return $(elem).find('.owl-access-description').length > 0;
      },
      setup: function(elem) {
        if (!owlAccess.a11y.description.hasDescription(elem)) {
          owlAccess.a11y.description.teardown(elem);
        }
        var descriptionID = owlAccess.util.uniqueID('owl-description');
        var message = "Pan through this carousel with the left and right arrow keys.";
        if (!!$(elem).attr('data-owl-carousel-accessmessage')) {
          message = $(elem).attr('data-owl-carousel-accessmessage');
        }
        var helper = owlAccess.elem.makeHiddenPara(
          message,
          descriptionID,
          "owl-access-description element-invisible"
        );
        $(elem).prepend(helper);
        $(elem).attr('aria-describedby', descriptionID);
        owlAccess.util.debug("description placed.");
      },
      teardown: function(elem) {
        var maybeDesc = $(elem).attr('aria-describedby');
        if (!!maybeDesc) {
          $('#' + maybeDesc).remove();
          $(elem).removeAttr('aria-describedby');
        }
      }
    },
    focus: {
      setup: function(elem, options){
        elem.focusin(owlAccess.events.eventResponse.focusIn);
        elem.focusout(owlAccess.events.eventResponse.focusOut);
      }
    },
    visibleItems: {
      markSlide: function(slide, isFocusable){

        var renderChildrenUnfocusable = function(elem) {
          $(elem).find('[tabindex]').each(function(){
            renderUnfocusable(this);
          });
          $(elem).find('a').not('[tabindex]').each(function(){
            renderUnfocusable(this);
          });
        };

        var renderUnfocusable = function(elem){
          var ti = $(elem).attr('tabindex');
          if (!ti) ti = "0";
          if (ti != "-1") {
            $(elem).attr('data-tabindex-default', ti)
                   .attr('tabindex', "-1");
          }
        };

        var renderFocusable = function(elem) {
          $(elem).attr('tabindex', $(elem).attr('data-tabindex-default'));
        };

        if (isFocusable) {
          $(slide).attr('aria-hidden', 'false')
                  .attr('tabindex', '0');
          $(slide).find('[data-tabindex-default]').each(function(){
            renderFocusable(this);
          });
        }
        else {
          $(slide).attr('aria-hidden', 'true')
                  .attr('tabindex', '-1');
          renderChildrenUnfocusable(slide);
        }
      },
      mark: function(owl) {
        for (var i = 0; i < owl.owlItems.length; i++) {
          owlAccess.a11y.visibleItems.markSlide(
            owl.owlItems[i],
            (owl.visibleItems.indexOf(i) >= 0)
          );
        }
      }
    },
    clearBlips: function(elem){
      $(elem).find('.owl-access-blip').remove();
    },
    triggerChanges: function(owl) {
      var blipID = owlAccess.util.uniqueID('owl-blip');
      var blip = owlAccess.elem.makeHiddenPara(
        "The carousel has moved to slide " + (owl.currentItem + 1) + ".",
        blipID,
        "owl-access-blip"
      );
      $(owl.baseElement).prepend(blip);
      owlAccess.util.debug("blip placed.");
      setTimeout(function(){
        owlAccess.a11y.clearBlips(owl.baseElement);
      }, 1000);
    }
  };

  // Element-handling functions

  owlAccess.elem = {
    markFocused: function(elem){
      $(elem).attr('data-owl-carousel-focused', '1');
    },
    markUnfocused: function(elem){
      $(elem).removeAttr('data-owl-carousel-focused');
    },
    ifFocused: function(elem, fn) {
      if ($(elem).attr('data-owl-carousel-focused') == '1') fn(elem);
    },
    ifUnfocused: function(elem, fn) {
      if ($(elem).attr('data-owl-carousel-focused') !== '1') fn(elem);
    },
    makeHiddenPara: function(message, id, className, additional){
      var newpAttrs = {
        id:             id,
        hidden:         true,
        'aria-hidden':  false
      };
      if (!!additional && $.isPlainObject(additional)) {
        $.extend(newpAttrs, additional);
      }
      var newp = document.createElement('p');
      newp.className = className;
      for (var i in newpAttrs) {
        newp.setAttribute(i, newpAttrs[i]);
      }
      newp.appendChild(document.createTextNode(message));
      return newp;
    },
    focused: function(e){
      var targ = $(e.target);
      if (targ.attr('data-owl-carousel-focusable') == 1) {
        return targ;
      }
      var closest = targ.closest('[data-owl-carousel-focusable="1"]');
      if (closest.length > 0) return closest;
      return null;
    },
    refocus: function(owl) {
      var focused = $(':focus');
      if (!!owl.baseElement.attr('data-owl-access-initialised')) {
        if (focused.length > 0) {
          var e = { target: focused };
          var targ = owlAccess.elem.focused(e);
          if (!!targ && targ.get(0) != focused.get(0)) {
            targ.focus();
          }
        }
      }
    }
  };

  // Event-handling functions

  owlAccess.events = {
    defaultAfterAction: function(){
      return function(){
        owlAccess.a11y.base.busy(this.owl.baseElement, false);
        owlAccess.a11y.visibleItems.mark(this.owl);
        owlAccess.a11y.triggerChanges(this.owl);
        owlAccess.elem.refocus(this.owl);
        owlAccess.util.debug("defaultAfterAction");
      };
    },
    props: {
      beforeInit : function(elem){
        owlAccess.a11y.base.setup(elem);
        owlAccess.a11y.focus.setup(elem, this.options);
      },
      afterInit  : function() {
        var owlBase = this.owl.baseElement;
        owlAccess.a11y.visibleItems.mark(this.owl);
        owlAccess.a11y.controls.setup(owlBase);
        owlAccess.a11y.description.setup(owlBase);
        this.reload();
        // Delay initialise finalisation by half a second
        // so we don't clobber initial focus
        setTimeout(function() {
          owlBase.attr('data-owl-access-initialised', '1');
        }, 500);
      },
      beforeUpdate: function() {
        owlAccess.a11y.description.teardown(this.owl.baseElement);
        owlAccess.a11y.base.busy(this.owl.baseElement, true);
        owlAccess.util.debug("beforeUpdate");
      },
      beforeMove: function() {
        owlAccess.a11y.description.teardown(this.owl.baseElement);
        owlAccess.a11y.base.busy(this.owl.baseElement, true);
        owlAccess.util.debug("beforeMove");
      },
      afterMove: function(){
        var act = owlAccess.events.defaultAfterAction();
        act.debounce(250).call(this);
        owlAccess.util.debug("afterMove");
      },
      afterUpdate: function() {
        var act = owlAccess.events.defaultAfterAction();
        act.debounce(250).call(this);
        owlAccess.util.debug("afterUpdate");
      }
    },
    mergeProps: function(props){
      var mergeProp = function(propName, props){
        var oaProp = owlAccess.events.props[propName];
        if (props.hasOwnProperty(propName)) {
          var p = props[propName];
          props[propName] = function(){
            p.apply(this, arguments);
            oaProp.apply(this, arguments);
          };
        }
        else {
          props[propName] = oaProp;
        }
        return props;
      };

      var newProps = $.extend({}, props);
      for (var propName in owlAccess.events.props) {
        newProps = mergeProp(propName, newProps);
      }
      return newProps;
    },
    eventResponse: {
      documentKeyUp: function(e) {
        var eventTarg = $(e.target),
        targ = owlAccess.elem.focused(e),
        action = null;

        if (!!targ) {
          if (e.keyCode == 37 || e.keyCode == 38) {
            action = "prev";
          }
          else if (e.keyCode == 39 || e.keyCode == 40) {
            action = "next";
          }
          else if (e.keyCode == 13) {
            if (eventTarg.hasClass('owl-prev')) action = "prev";
            else if (eventTarg.hasClass('owl-next')) action = "next";
          }
          if (!!action) {
            targ.trigger('owl.' + action);
          }
        }
      },
      focusIn: function(e){
        owlAccess.elem.ifUnfocused(this, function(elem){
          var autoPlay = $(elem).data('owlCarousel').options.autoPlay;
          owlAccess.elem.markFocused(elem);
          owlAccess.a11y.clearBlips(elem);
          owlAccess.a11y.description.setup(elem);
          if (!!autoPlay) {
            $(elem).data('owlCarouselAutoPlaySpeed', autoPlay);
            $(elem).trigger('owl.stop');
          }
          owlAccess.util.debug("focusInStopOnHover");
        });
      },
      focusOut: function(e){
        owlAccess.elem.ifFocused(this, function(elem){
          var autoPlay = $(elem).data('owlCarouselAutoPlaySpeed');
          owlAccess.elem.markUnfocused(elem);
          owlAccess.a11y.description.teardown(elem);
          if (!!autoPlay) {
            $(elem).trigger('owl.play', autoPlay);
          }
          owlAccess.util.debug("focusOutStopOnOver");
        });
      }
    }
  };

})(jQuery);